#define _POSIX_C_SOURCE 200112L

#include "common_socket.h"
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>

#define ERROR -1
#define SUCCESS 0

// Setea todos los hints en 0 y modifica el valor de algunos.
static void _setHints(struct addrinfo* hints);

// Itera en las posibles direcciones hasta que se puede enlazar (bind).
// En caso de éxito modifica el fd del socket y devuelve 0.
// Retorna -1 en caso contrario.
static int _tryToBind(Socket* self, struct addrinfo* results);

// Verifica si se pudo enlazar el fd con la dirección recibida.
// Retorna true en caso positivo y false en caso contrario.
static bool _couldBind(int socket_fd, struct addrinfo* info);

// Itera en las posibles direcciones hasta que se puede establecer una conexión.
// En caso de éxito modifica el fd del socket y devuelve 0.
// Retorna -1 en caso contrario.
static int _tryToConnect(Socket* self, struct addrinfo* results);

// Verifica si se pudo establecer una conexión entre el fd y la dirección
// recibida. Retorna true en caso positivo y false en caso contrario.
static bool _couldConnect(int socket_fd, struct addrinfo* info);


void socketInit(Socket* self) {
    self->fd = -1;
}

int socketBindAndListen(Socket* self,
                        const char* service, int acceptance) {
    struct addrinfo hints;
    struct addrinfo *results;

    _setHints(&hints);
    hints.ai_flags = AI_PASSIVE;

    int status = getaddrinfo(NULL, service, &hints, &results);
    if (status != SUCCESS) {
        fprintf(stderr, "Error en getaddrinfo: %s.\n",
                gai_strerror(status));
        return ERROR;
    }
    if (_tryToBind(self, results) == SUCCESS) {
        if (listen(self->fd, acceptance) == ERROR){
            fprintf(stderr, "Error: %s\n", strerror(errno));
            return ERROR;
        }
        return SUCCESS;
    }
    return ERROR;
}

int socketAccept(Socket* listener, Socket* peer) {
    int peer_fd = accept(listener->fd, NULL, NULL);
    if (peer_fd == ERROR) {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        return ERROR;
    }
    peer->fd = peer_fd;
    return SUCCESS;
}

int socketConnect(Socket* self, const char* host, const char* service) {
    struct addrinfo hints;
    struct addrinfo *results;

    _setHints(&hints);
    hints.ai_flags = 0;

    int status = getaddrinfo(host, service, &hints, &results);
    if (status != SUCCESS) {
        fprintf(stderr, "Error en getaddrinfo: %s.\n",
                gai_strerror(status));
        return ERROR;
    }
    return _tryToConnect(self, results);
}


int socketSend(Socket* self, const void* buffer, size_t length) {
    bool error_at_sending = false;
    uint8_t* address = (uint8_t*)buffer;  // casteo para realizar operaciones
    int bytes_sent = 0;                   // ariméticas con dicha  dirección

    while (bytes_sent < length && !error_at_sending) {
        int sent = send(self->fd, address,length-bytes_sent, MSG_NOSIGNAL);
        if (sent == ERROR) {
            fprintf(stderr,"Error: %s\n", strerror(errno));
            error_at_sending = true;
        } else {
            bytes_sent += sent;
            address += sent;
        }
    }
    return error_at_sending? ERROR : bytes_sent;
}

int socketReceive(Socket* self, void* buffer, size_t length) {
    bool valid_socket = true, zero_bytes_recv = false;
    uint8_t* address = (uint8_t*)buffer;  // casteo para realizar operaciones
    int bytes_received = 0;               // ariméticas con dicha  dirección

    while (bytes_received < length && valid_socket && !zero_bytes_recv) {
        int received = recv(self->fd, address,
                        length - bytes_received, MSG_NOSIGNAL);
        if (received == ERROR) {
            fprintf(stderr, "Error: %s\n", strerror(errno));
            valid_socket = false;
        } else if (received == 0){
            zero_bytes_recv = true;
        }else {
            bytes_received += received;
            address += received;
        }
    }
    return valid_socket?  bytes_received: ERROR;
}

void socketRelease(Socket* self) {
    shutdown(self->fd, SHUT_RDWR);
    close(self->fd);
}

//---------------------------- Funciones privadas ----------------------------//

static void _setHints(struct addrinfo* hints){
    memset(hints, 0, sizeof(struct addrinfo));
    hints->ai_family = AF_INET;
    hints->ai_socktype = SOCK_STREAM;
}

static int _tryToBind(Socket* self, struct addrinfo* results){
    bool binded = false;
    int socket_fd = 0;
    struct addrinfo *aux;

    for (aux = results; (aux != NULL) && (!binded); aux = aux->ai_next) {
        socket_fd = socket(aux->ai_family, aux->ai_socktype, aux->ai_protocol);
        binded = _couldBind(socket_fd, aux);
    }
    freeaddrinfo(results);
    if (!binded) {
        fprintf(stderr, "No se pudo enlazar.\n");
        return ERROR;
    }
    self->fd = socket_fd;
    return SUCCESS;
}

static bool _couldBind(int socket_fd, struct addrinfo* info){
    int status = ERROR;

    if (socket_fd == ERROR) {
        fprintf(stderr,"Error: %s\n", strerror(errno));
    } else {
        int val = 1;
        setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
        status = bind(socket_fd, info->ai_addr, info->ai_addrlen);
        if (status== ERROR) {
            fprintf(stderr, "Error: %s.\n", strerror(errno));
            close(socket_fd);
        }
    }
    return (status != ERROR);
}

static int _tryToConnect(Socket* self, struct addrinfo* results){
    bool connected = false;
    int socket_fd = 0;
    struct addrinfo *aux;

    for (aux = results; (aux != NULL) && (!connected); aux = aux->ai_next) {
        socket_fd = socket(aux->ai_family, aux->ai_socktype, aux->ai_protocol);
        connected = _couldConnect(socket_fd, aux);
    }
    freeaddrinfo(results);
    if (!connected) {
        fprintf(stderr, "No se pudo conectar.\n");
        return ERROR;
    }
    self->fd = socket_fd;
    return SUCCESS;
}

static bool _couldConnect(int socket_fd, struct addrinfo* info){
    int status = ERROR;

    if (socket_fd == ERROR) {
        fprintf(stderr,"Error: %s\n", strerror(errno));
    } else {
        status = connect(socket_fd, info->ai_addr, info->ai_addrlen);
        if (status== ERROR) {
            fprintf(stderr, "Error: %s.\n", strerror(errno));
            close(socket_fd);
        }
    }
    return (status != ERROR);
}

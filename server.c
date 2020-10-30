#include "server.h"
#include "common_cipher.h"
#include <string.h>

#define SUCCESS 0
#define ERROR -1
#define CHUNK_SIZE 64
#define KEY_SIZE 50
#define METHOD_SIZE 30

// Recibe y decodifica los mensajes recibidos, escribiendo el resultado en
// 'output_file'
static ssize_t _receiveAndDecode(Server *server, Cipher *cipher,
                                 FILE *output_file, const char *key);

void serverInit(Server *server, const char *service) {
    socketInit(&server->socket);
    socketInit(&server->peer);
    server->service = service;
    server->peer_closed = true;
}

int serverBindAndListen(Server *server, int acceptance) {
    return socketBindAndListen(&(server->socket), server->service, acceptance);
}

int serverAccept(Server *server) {
    int status = socketAccept(&(server->socket), &(server->peer));
    if (status == SUCCESS){
        server->peer_closed = false;
    }
    return status;
}

ssize_t serverReceiveAndDecrypt(Server *server, FILE *output_file,
                                const char *method, const char *key) {
    Cipher cipher;
    if (cipherInit(&cipher, method, key) == ERROR){
        return ERROR;
    }
    ssize_t status = _receiveAndDecode(server, &cipher, output_file, key);
    cipherRelease(&cipher);
    return status;
}

void serverDisconnectAndRelease(Server *server) {
    socketRelease(&(server->socket));
    if (!(server->peer_closed)){
        socketRelease(&(server->peer));
    }
}


//---------------------------- Funciones privadas ----------------------------//

static ssize_t _receiveAndDecode(Server *server, Cipher *cipher,
                                 FILE *output_file, const char *key) {
    ssize_t info_received = 0, received = -1;
    int status;
    char input_chunk[CHUNK_SIZE], output_chunk[CHUNK_SIZE+1];
    memset(input_chunk, 0, CHUNK_SIZE);
    memset(output_chunk, 0, CHUNK_SIZE+1);
    while (received!=0){
        received = socketReceive(&(server->peer), input_chunk, CHUNK_SIZE);
        if (received != ERROR){
            status = cipherDecode(cipher, input_chunk, received, output_chunk,
                                  CHUNK_SIZE+1);
            if (status != ERROR){
                fwrite(output_chunk, sizeof(char), received, output_file);
            }
        }
        if (received == ERROR || status == ERROR){
            socketRelease(&(server->peer));
            server->peer_closed = true;
            return ERROR;
        }
        info_received += received;
    }
    return info_received;
}

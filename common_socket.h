#ifndef TP1_COMMON_SOCKET_H
#define TP1_COMMON_SOCKET_H
#include <stdlib.h>

typedef struct {
    int fd;
}Socket;

// Inicializa el fd del socket recibido en -1
void socketInit(Socket* self);

// Se cierra el socket
void socketRelease(Socket* self);

// Enlaza una dirección al socket de acuerdo al 'service' requerido.
// Establece una lista de espera de acuerdo a 'acceptance' y retorna 0 en
// caso de éxito, y -1 si surgió un error, mostrandolo por pantalla.
int socketBindAndListen(Socket* self, const char* service, int acceptance);

// Acepta la conexión de la primer petición de conexión de la lista de espera.
// Asigna a peer el fd asociado al socket aceptado.
// Retorna 0 en caso de éxito y -1 si surgió un error, mostrandolo por pantalla.
int socketAccept(Socket* listener, Socket* peer);

// Conecta el socket a una dirección de acuerdo al 'host' y al 'service'
// requerido. Retorna 0 en caso de éxito, y -1 si surgió un error, mostrandolo
// por pantalla.
int socketConnect(Socket* self, const char* host, const char* service);

// Envía 'length' bytes del 'buffer'. Retorna la cantidad de bytes enviados
// en caso de éxito y -1 si hubo algún error, monstrandolo por pantalla.
int socketSend(Socket* self, const void* buffer, size_t length);

// Recibe una cantidad de bytes menor o igual a 'length' y la carga en 'buffer'.
// Retorna la cantidad de bytes recibidos en caso de éxito y -1
// si hubo algún error, monstrandolo por pantalla.
int socketReceive(Socket* self, void* buffer, size_t length);


#endif

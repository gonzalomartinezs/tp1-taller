#ifndef TP1_SERVER_H
#define TP1_SERVER_H

#include "common_socket.h"
#include <stdio.h>
#include <stdbool.h>

// Los artibutos son privados
typedef struct{
    Socket socket;
    Socket peer;
    bool peer_closed;
    const char* service;
}Server;

// Inicializa el servidor.
void serverInit(Server* server, const char* service);

// Deja el server listo para recibir conexiones, armando una lista de espera
// de acuerdo a 'acceptance'.
int serverBindAndListen(Server* server, int acceptance);

// El server accepta la conexión que está en primer lugar en la lista de espera.
int serverAccept(Server *server);

// Desncripta la información recibida utilizando el 'method' y la 'key'
// ingresados. Posteriormente, escribe el contenido desencriptado en 'file'.
// Retorna la cantidad de bytes recibidos en caso de éxito y -1 caso contrario.
ssize_t serverReceiveAndDecrypt(Server *server, FILE* output_file,
                                const char* method, const char* key);

void serverDisconnectAndRelease(Server* server);

#endif

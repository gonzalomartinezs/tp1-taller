#ifndef TP1_CLIENT_H
#define TP1_CLIENT_H

#include <stdio.h>
#include "common_socket.h"

// Los artibutos son privados
typedef struct{
    Socket socket;
    const char* host;
    const char* service;
}Client;

// Inicializa el cliente.
void clientInit(Client* client, const char* host, const char* service);

// Conecta el cliente al servidor.
// Retorna 0 en caso de éxito, y -1 si surgió un error.
int clientConnect(Client* client);

// Encripta el contenido del archivo 'file' utilizando el 'method' y la 'key'
// ingresados. Posteriormente, envía el contenido encriptado al servidor.
// Retorna la cantidad de bytes enviados en caso de éxito y -1 en caso contrario
ssize_t clientEncryptAndSend(Client *client, FILE *input_file,
                             const char *method, const char *key);

// Libera los recuros del cliente.
void clientDisconnectAndRelease(Client* client);

#endif

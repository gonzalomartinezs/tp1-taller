#ifndef TP1_CLIENT_H
#define TP1_CLIENT_H

#include <stdio.h>
#include "common_socket.h"

typedef struct{
    Socket* socket;
    const char* host;
    const char* service;
}Client;

void clientInit(Client* client, const char* host, const char* service);

int clientConnect(Client* client);

int clientEncryptAndSend(Client *client, FILE *input_file, const char *method,
                         const char *key);

void clientDisconnectAndRelease(Client* client);

#endif
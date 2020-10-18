#ifndef TP1_SERVER_H
#define TP1_SERVER_H

#include "common_socket.h"
#include <stdio.h>

typedef struct{
    Socket socket;
    const char* service;
}Server;

void serverInit(Server* server, const char* service);

int serverBindAndListen(Server* server, int acceptance);

int serverAccept(Server server, Socket *peer);

int serverReceiveAndDecrypt(Socket *peer, FILE* output_file,
                            const char* recv_method, const char* recv_key);

void serverDisconnectAndRelease(Server* server);

#endif

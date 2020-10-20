#include <stdio.h>
#include "server.h"

#define SUCCESS 0
#define ERROR 1
#define SERVER_ERROR -1
#define ARGS_AMOUNT 4

int main(int argc, char** argv) {
    if (argc != ARGS_AMOUNT){
        fprintf(stderr,"Cantidad de argumentos errónea.\n");
        return ERROR;
    }

    Server server;
    serverInit(&server, argv[1]);
    serverBindAndListen(&server, 5);

    Socket peer;
    socketInit(&peer);
    serverAccept(&server, &peer);

    int status = serverReceiveAndDecrypt(&peer, stdout, argv[2], argv[3]);
    if (status != SERVER_ERROR){
        socketRelease(&peer);
        serverDisconnectAndRelease(&server);
        return SUCCESS;
    }
    serverDisconnectAndRelease(&server);
    return ERROR;
}

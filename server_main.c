#include <stdio.h>
#include "server.h"
#define ERROR -1

int main(int argc, char** argv) {
    if(argc !=3){
        fprintf(stderr,"Cantidad de argumentos invalida\n");
        return ERROR;
    }

    Server server;
    serverInit(&server, argv[1]);
    serverBindAndListen(&server, 5);

    Socket peer;
    socketInit(&peer);
    serverAccept(server, &peer);
    if(serverReceiveAndDecrypt(&peer, stdout, "vigenere", argv[2]) == ERROR){
        serverDisconnectAndRelease(&server);
        return ERROR;
    }
    socketRelease(&peer);
    serverDisconnectAndRelease(&server);
    return 0;
}

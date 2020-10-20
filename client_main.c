#include "client.h"
#include <stdio.h>

#define SUCCESS 0
#define ERROR 1
#define CLIENT_ERROR -1
#define ARGS_AMOUNT 5

int main(int argc, char** argv){
    if (argc != ARGS_AMOUNT){
        fprintf(stderr,"Cantidad de argumentos errónea.\n");
        return ERROR;
    }
    Client client;
    clientInit(&client, argv[1], argv[2]);
    clientConnect(&client);

    int status = clientEncryptAndSend(&client, stdin, argv[3], argv[4]);

    if (status != CLIENT_ERROR){
        clientDisconnectAndRelease(&client);
        return SUCCESS;
    }
    return ERROR;
}


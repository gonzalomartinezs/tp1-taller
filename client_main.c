#include "client.h"
#include <stdio.h>

#define ERROR -1

int main(int argc, char** argv){
    if(argc !=4){
        printf("Cantidad de argumentos erronea.\n");
        return ERROR;
    }
    Client client;
    clientInit(&client, argv[1], argv[2]);
    clientConnect(&client);
    if(clientEncryptAndSend(&client, stdin, "vigenere", argv[3])==-1){
        return -1;
    }
    clientDisconnectAndRelease(&client);
    return 0;
}


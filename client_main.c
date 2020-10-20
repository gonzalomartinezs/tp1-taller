#include "client.h"
#include <stdio.h>
#include "common_command_parser.h"

#define SUCCESS 0
#define ERROR 1
#define CLIENT_ERROR -1

int main(int argc, char** argv){
    char host[HOST_SIZE];
    char service[SERVICE_SIZE];
    char method[METHOD_SIZE];
    char key[KEY_SIZE];

    if (commandParserClient(argc, argv, host, service, method, key) == SUCCESS){
        Client client;
        clientInit(&client, host, service);
        clientConnect(&client);

        ssize_t status = clientEncryptAndSend(&client, stdin, method, key);

        if (status != CLIENT_ERROR){
            clientDisconnectAndRelease(&client);
            return SUCCESS;
        }
    }
    return ERROR;
}


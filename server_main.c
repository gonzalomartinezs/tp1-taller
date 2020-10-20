#include <stdio.h>
#include "server.h"
#include "common_command_parser.h"

#define SUCCESS 0
#define ERROR 1
#define SERVER_ERROR -1

int main(int argc, char** argv) {
    char service[SERVICE_SIZE];
    char method[METHOD_SIZE];
    char key[KEY_SIZE];

    if (commandParserServer(argc, argv, service, method, key) == SUCCESS){
        Server server;
        serverInit(&server, service);
        serverBindAndListen(&server, 5);
        serverAccept(&server);

        ssize_t status = serverReceiveAndDecrypt(&server, stdout, method, key);
        serverDisconnectAndRelease(&server);

        if (status != SERVER_ERROR) {
            return SUCCESS;
        }
    }
    return ERROR;
}

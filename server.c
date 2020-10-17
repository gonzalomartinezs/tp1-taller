#include <string.h>
#include "server.h"
#include "common_cipher.h"
#define SUCCESS 0
#define ERROR -1
#define CHUNK_SIZE 64

int _receiveAndDecode(Socket *peer, Cipher *cipher, FILE *output_file,
                      const char *key);

void serverInit(Server *server, const char *service) {
    Socket socket;
    server->socket = &socket;
    socketInit(server->socket);
    server->service = service;
}

int serverBindAndListen(Server *server, int acceptance) {
    return socketBindAndListen(server->socket, server->service, acceptance);
}

int serverAccept(Server server, Socket *peer) {
    return socketAccept(server.socket, peer);
}

int serverReceiveAndDecrypt(Socket *peer, FILE *output_file,
                            const char *method, const char *key) {
    Cipher cipher;
    if (cipherInit(&cipher, method) == ERROR){
        return ERROR;
    }
    int status = _receiveAndDecode(peer, &cipher, output_file, key);
    cipherRelease(&cipher);
    return status;
}

void serverDisconnectAndRelease(Server *server) {
    socketRelease(server->socket);
}


//---------------------------- Funciones privadas ----------------------------//

int _receiveAndDecode(Socket *peer, Cipher *cipher, FILE *output_file,
                      const char *key) {
    int info_received = 0, received = -1;
    int status;
    char input_chunk[CHUNK_SIZE], output_chunk[CHUNK_SIZE];
    memset(input_chunk, 0, CHUNK_SIZE);
    memset(output_chunk, 0, CHUNK_SIZE);

    while(received!=0){
        received = socketReceive(peer, input_chunk, CHUNK_SIZE);
        if(received != ERROR){
            status = cipherDecode(cipher, input_chunk, output_chunk,
                                  CHUNK_SIZE, key);
            if(status != ERROR){
                fwrite(output_chunk, sizeof(char), received, output_file);
            }
        }
        if (status == ERROR || received == ERROR){
            socketRelease(peer);
            return ERROR;
        }
        info_received += received;
    }
    return info_received;
}

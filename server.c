#include "server.h"
#include "common_cipher.h"
#include <string.h>
#include <stdbool.h>

#define SUCCESS 0
#define ERROR -1
#define CHUNK_SIZE 64
#define KEY_SIZE 50
#define METHOD_SIZE 30

// Recibe y decodifica los mensajes recibidos, escribiendo el resultado en
// 'output_file'
static int _receiveAndDecode(Socket *peer, Cipher *cipher, FILE *output_file,
                      const char *key);

void serverInit(Server *server, const char *service) {
    Socket socket;
    socketInit(&socket);
    server->socket = socket;
    server->service = service;
}

int serverBindAndListen(Server *server, int acceptance) {
    return socketBindAndListen(&(server->socket), server->service, acceptance);
}

int serverAccept(Server *server, Socket *peer) {
    return socketAccept(&(server->socket), peer);
}

int serverReceiveAndDecrypt(Socket *peer, FILE *output_file,
                            const char *method, const char *key) {
    Cipher cipher;
    if (cipherInit(&cipher, method, key) == ERROR){
        return ERROR;
    }
    int status = _receiveAndDecode(peer, &cipher, output_file, key);
    cipherRelease(&cipher);
    return status;
}

void serverDisconnectAndRelease(Server *server) {
    socketRelease(&(server->socket));
}


//---------------------------- Funciones privadas ----------------------------//

static int _receiveAndDecode(Socket *peer, Cipher *cipher, FILE *output_file,
                      const char *key) {
    int info_received = 0, received = -1;
    int status;
    char input_chunk[CHUNK_SIZE], output_chunk[CHUNK_SIZE+1];
    memset(input_chunk, 0, CHUNK_SIZE);
    memset(output_chunk, 0, CHUNK_SIZE+1);
    while (received!=0){
        received = socketReceive(peer, input_chunk, CHUNK_SIZE);
        if (received != ERROR){
            status = cipherDecode(cipher, input_chunk, received, output_chunk,
                                  CHUNK_SIZE+1, key);
            if (status != ERROR){
                fwrite(output_chunk, sizeof(char), received, output_file);
            }
        }
        if (received == ERROR || status == ERROR){
            socketRelease(peer);
            return ERROR;
        }
        info_received += received;
    }
    return info_received;
}

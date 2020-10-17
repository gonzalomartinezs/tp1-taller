#include "client.h"
#include "common_cipher.h"
#include <stdio.h>
#include <string.h>

#define SUCCESS 0
#define ERROR -1
#define CHUNK_SIZE 64

// Lee el archivo y envía mensajes encriptados de tamaño CHUNK_SIZE
int _encodeAndSend(Client* client, Cipher* cipher, FILE* file, const char *key);

void clientInit(Client *client, const char *host, const char *service) {
    Socket socket;
    client->socket = &socket;
    socketInit(client->socket);
    client->host = host;
    client->service = service;
}

int clientEncryptAndSend(Client *client, FILE *input_file, const char *method,
                         const char *key) {
    Cipher cipher;
    if (cipherInit(&cipher, method) == ERROR){
        return ERROR;
    }
    int status = _encodeAndSend(client, &cipher, input_file, key);
    cipherRelease(&cipher);
    return status;
}

int clientConnect(Client *client) {
    return socketConnect(client->socket, client->host, client->service);
}

void clientDisconnectAndRelease(Client *client) {
    socketRelease(client->socket);
}

//---------------------------- Funciones privadas ----------------------------//

int _encodeAndSend(Client* client, Cipher* cipher, FILE* file, const char *key){
    int info_sent = 0;
    int status, sent;
    size_t read;
    char input_chunk[CHUNK_SIZE], output_chunk[CHUNK_SIZE];
    memset(input_chunk, 0, CHUNK_SIZE);
    memset(output_chunk, 0, CHUNK_SIZE);

    while(!feof(file)){
        read = fread(input_chunk, sizeof(char), CHUNK_SIZE, file);
        status = cipherEncode(cipher, input_chunk, output_chunk,
                              CHUNK_SIZE, key);

        if (status != ERROR) {
            sent = socketSend(client->socket, output_chunk, read);
        }
        if (status == ERROR || sent == ERROR){
            clientDisconnectAndRelease(client);
            return ERROR;
        }
        info_sent += sent;
    }
    return info_sent;
}
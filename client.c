#include "client.h"
#include "common_cipher.h"
#include <stdio.h>
#include <string.h>

#define SUCCESS 0
#define ERROR -1
#define CHUNK_SIZE 64
#define KEY_SIZE 50
#define METHOD_SIZE 30

// Lee el archivo y envía mensajes encriptados de tamaño CHUNK_SIZE
static ssize_t _encodeAndSend(Client* client, Cipher* cipher, FILE* file,
                       const char *key);

void clientInit(Client *client, const char *host, const char *service) {
    socketInit(&client->socket);
    client->host = host;
    client->service = service;
}

ssize_t clientEncryptAndSend(Client *client, FILE *input_file,
                             const char *method, const char *key) {
    Cipher cipher;
    if (cipherInit(&cipher, method, key) == ERROR){
        return ERROR;
    }
    ssize_t status = _encodeAndSend(client, &cipher, input_file, key);
    cipherRelease(&cipher);
    return status;
}

int clientConnect(Client *client) {
    return socketConnect(&(client->socket), client->host, client->service);
}

void clientDisconnectAndRelease(Client *client) {
    socketRelease(&(client->socket));
}

//---------------------------- Funciones privadas ----------------------------//

static ssize_t _encodeAndSend(Client* client, Cipher* cipher, FILE* file,
                       const char *key){
    ssize_t info_sent = 0;
    ssize_t sent;
    char input_chunk[CHUNK_SIZE], output_chunk[CHUNK_SIZE+1];
    memset(input_chunk, 0, CHUNK_SIZE);
    memset(output_chunk, 0, CHUNK_SIZE+1);
    while (!feof(file)){
        size_t read = fread(input_chunk, sizeof(char), CHUNK_SIZE, file);
        int status = cipherEncode(cipher, input_chunk, read, output_chunk,
                              CHUNK_SIZE+1);

        if (status != ERROR) {
            sent = socketSend(&(client->socket), output_chunk, read);
        }
        if (status == ERROR || sent == ERROR){
            clientDisconnectAndRelease(client);
            return ERROR;
        }
        info_sent += sent;
    }
    return info_sent;
}

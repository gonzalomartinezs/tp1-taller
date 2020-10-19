#include "client.h"
#include "common_cipher.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define SUCCESS 0
#define ERROR -1
#define CHUNK_SIZE 64
#define KEY_SIZE 50
#define METHOD_SIZE 30

// Carga en 'option' la opción introducida por el usuario para dicho campo
void _extractOption(const char *recv_option, char *option);

// Lee el archivo y envía mensajes encriptados de tamaño CHUNK_SIZE
int _encodeAndSend(Client* client, Cipher* cipher, FILE* file, const char *key);

void clientInit(Client *client, const char *host, const char *service) {
    Socket socket;
    socketInit(&socket);
    client->socket = socket;
    client->host = host;
    client->service = service;
}

int clientEncryptAndSend(Client *client, FILE *input_file,
                         const char *recv_method, const char *recv_key) {
    char key[KEY_SIZE], method[METHOD_SIZE];
    memset(key, 0, KEY_SIZE);
    memset(method, 0, METHOD_SIZE);
    _extractOption(recv_key, key);
    _extractOption(recv_method, method);

    Cipher cipher;
    if (cipherInit(&cipher, method) == ERROR){
        return ERROR;
    }
    int status = _encodeAndSend(client, &cipher, input_file, key);
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

void _extractOption(const char *recv_option, char *option){
    bool eq_sign_found = false;
    int j = 0;
    int length = (int)strlen(recv_option);
    for (int i=0; i<length; i++){
        if (eq_sign_found && recv_option[i] != '"'){
            option[j] = recv_option[i];
            j++;
        } else if (recv_option[i]=='='){
            eq_sign_found = true;
        }
    }
}

int _encodeAndSend(Client* client, Cipher* cipher, FILE* file, const char *key){
    int info_sent = 0;
    int sent;
    char input_chunk[CHUNK_SIZE], output_chunk[CHUNK_SIZE+1];
    memset(input_chunk, 0, CHUNK_SIZE);
    memset(output_chunk, 0, CHUNK_SIZE+1);

    while (!feof(file)){
        size_t read = fread(input_chunk, sizeof(char), CHUNK_SIZE, file);
        int status = cipherEncode(cipher, input_chunk, read, output_chunk,
                              CHUNK_SIZE+1, key);

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

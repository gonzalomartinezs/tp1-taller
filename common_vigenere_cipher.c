#include "common_vigenere_cipher.h"
#include <string.h>
#include <stdio.h>

#define SUCCESS 0
#define INSUF_BUFF_SIZE -1
#define VOCAB_SIZE 256
#define MAX_INPUT_SIZE 64

// Repite la clave hasta alcanzar la longitd del mensaje.
static void _extendKey(VigenereCipher* cipher, int length, char *extended_key);


void vigenereCipherInit(VigenereCipher *cipher, const char *key) {
    cipher->key = key;
    cipher->position_in_key = 0;
}

int vigenereCipherEncode(VigenereCipher* cipher, const char *input,
                         size_t length, char *output, size_t buff_size) {
    if (length + 1 > buff_size){
        fprintf(stderr, "Error: tamaño insuficiente de buffer.");
        return INSUF_BUFF_SIZE;
    }
    char extended_key[MAX_INPUT_SIZE];
    _extendKey(cipher, length, extended_key);
    for (int i=0; i<length; i++){
        output[i] = (char)((input[i] + extended_key[i])%VOCAB_SIZE);
    }
    return SUCCESS;
}

int vigenereCipherDecode(VigenereCipher* cipher, const char *input,
                         size_t length, char *output, size_t buff_size) {
    if (length + 1 > buff_size) {
        fprintf(stderr, "Error: tamaño insuficiente de buffer.");
        return INSUF_BUFF_SIZE;
    }
    char extended_key[MAX_INPUT_SIZE];
    _extendKey(cipher, length, extended_key);
    for (int i=0; i<length; i++) {
        output[i] = (char) ((input[i] - extended_key[i]) % VOCAB_SIZE);
    }
    return SUCCESS;
}

void vigenereCipherRelease(VigenereCipher *vigenere) {
    // do nothing
}


//---------------------------- Funciones privadas ----------------------------//

static void _extendKey(VigenereCipher* cipher, int length, char *extended_key){
    memset(extended_key, 0, MAX_INPUT_SIZE);

    int key_length = (int)strlen(cipher->key);
    if (key_length != 0){
        int position;
        for (int i=0; i<length; i++){
            position = (cipher->position_in_key + i) % key_length;
            extended_key[i] = cipher->key[position];
        }
       cipher->position_in_key = (position + 1) % key_length;
    }
}

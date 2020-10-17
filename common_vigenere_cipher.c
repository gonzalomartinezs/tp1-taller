#include "common_vigenere_cipher.h"
#include <string.h>
#include <stdio.h>

#define SUCCESS 0
#define INSUF_BUFF_SIZE -1
#define VOCAB_SIZE 256
#define MAX_INPUT_SIZE 64


// Repite la clave hasta alcanzar la longitd del mensaje.
void *_extendKey(const char *key, int length, char *extended_key);

// Pre: el buffer size de 'output' es mayor o igual al de 'input'.
// Post: toma el mensaje de 'input' y coloca su codificación
//       Vigenere en 'output' usando 'key' como clave.
//       Retorna 0 en caso de éxito, 1 caso contrario.
int _vigenereEncode(const char *input, size_t length, char *output,
                    size_t buff_size, const char *key);

// Pre: el buffer size de 'output' es mayor o igual al de 'input'.
// Post: toma el mensaje codificado 'input' y coloca su
//       decodificación Vigenere en 'output' usando 'key' como clave.
//       Retorna 0 en caso de éxito, 1 caso contrario.
int _vigenereDecode(const char *input, size_t length, char *output,
                    size_t buff_size, const char *key);


void vigenereCipherInit(VigenereCipher *vigenere) {
    vigenere->encode = &_vigenereEncode;
    vigenere->decode = &_vigenereDecode;
}

EncryptFunc getVigenereEncoding(VigenereCipher *vigenere) {
    return vigenere->encode;
}

EncryptFunc getVigenereDecoding(VigenereCipher *vigenere) {
    return vigenere->decode;
}

void vigenereCipherRelease(VigenereCipher *vigenere) {
    // do nothing
}


//---------------------------- Funciones privadas ----------------------------//

int _vigenereEncode(const char *input, size_t length, char *output,
                    size_t buff_size, const char *key) {
    if (length+1 > buff_size){
        fprintf(stderr, "Error: tamaño insuficiente de buffer.");
        return INSUF_BUFF_SIZE;
    }
    char extended_key[MAX_INPUT_SIZE];
    _extendKey(key, length, extended_key);
    for (int i=0; i<length; i++){
        output[i] = (char)((input[i]+extended_key[i])%VOCAB_SIZE);
    }
    return SUCCESS;
}

int _vigenereDecode(const char *input, size_t length, char *output,
                    size_t buff_size, const char *key) {
    if (length+1 > buff_size){
        fprintf(stderr, "Error: tamaño insuficiente de buffer.");
        return INSUF_BUFF_SIZE;
    }
    char extended_key[MAX_INPUT_SIZE];
    _extendKey(key, length, extended_key);
    for (int i=0; i<length; i++){
        output[i] = (char)((input[i]-extended_key[i])%VOCAB_SIZE);
    }
    return SUCCESS;
}


void *_extendKey(const char *key, int length, char *extended_key) {
    int key_length = (int)strlen(key);
    memset(extended_key, 0, MAX_INPUT_SIZE);

    for (int i=0; i<length; i++){
        extended_key[i] = key[i%key_length];
    }
    return extended_key;
}

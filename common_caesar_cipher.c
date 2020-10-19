#include "common_caesar_cipher.h"
#include <string.h>
#include <stdio.h>

#define SUCCESS 0
#define VOCAB_SIZE 256
#define INSUF_BUFF_SIZE -1

// Pre: el buffer size de 'output' es mayor o igual al de 'input'.
// Post: toma el mensaje de 'input' y coloca su codificación
//       Cesar en 'output' usando 'key' como clave.
//       Retorna 0 en caso de éxito, 1 caso contrario.
int _caesarEncode(const char *input, size_t length, char *output,
                  size_t buff_size, const char *key, void *aux);

// Pre: el buffer size de 'output' es mayor o igual al de 'input'.
// Post: toma el mensaje codificado 'input' y coloca su
//       decodificación Cesar en 'output' usando 'key' como clave.
//       Retorna 0 en caso de éxito, 1 caso contrario.
int _caesarDecode(const char *input, size_t length, char *output,
                  size_t buff_size, const char *key, void *aux);


void caesarCipherInit(CaesarCipher *caesar) {
    caesar->encode = &_caesarEncode;
    caesar->decode = &_caesarDecode;
}

EncryptFunc getCaesarEncoding(CaesarCipher *caesar) {
    return caesar->encode;
}

EncryptFunc getCaesarDecoding(CaesarCipher *caesar) {
    return caesar->decode;
}

void caesarCipherRelease(CaesarCipher *caesar) {
    //do nothing
}



//---------------------------- Funciones privadas ----------------------------//

int
_caesarEncode(const char *input, size_t length, char *output, size_t buff_size,
              const char *key, void *aux) {
    int true_key = atoi(key);
    if (length+1 > buff_size){
        fprintf(stderr, "Error: tamaño insuficiente de buffer.");
        return INSUF_BUFF_SIZE;
    }
    for (int i=0; i<length; i++){
        output[i] = (char)((input[i]+true_key)%VOCAB_SIZE);
    }
    return SUCCESS;
}


int
_caesarDecode(const char *input, size_t length, char *output, size_t buff_size,
              const char *key, void *aux) {
    int true_key = atoi(key);
    if (length+1 > buff_size){
        fprintf(stderr, "Error: tamaño insuficiente de buffer.");
        return INSUF_BUFF_SIZE;
    }
    for (int i=0; i<length; i++){
        output[i] = (char)((input[i]-true_key)%VOCAB_SIZE);
    }
    return SUCCESS;
}



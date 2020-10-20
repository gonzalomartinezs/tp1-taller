#include "common_rc4_cipher.h"
#include <string.h>
#include <stdio.h>

#define INSUF_BUFF_SIZE -1

// Pre: el buffer size de 'output' es mayor o igual al de 'input'.
// Post: toma el mensaje de 'input' y coloca su codificación
//       RC4 en 'output' usando 'key' como clave.
//       Retorna 0 en caso de éxito, 1 caso contrario.
int _rc4Encode(const char *input, size_t length, char *output, size_t buff_size,
               const char *key, CipherInfo *info);

// Pre: el buffer size de 'output' es mayor o igual al de 'input'.
// Post: toma el mensaje codificado 'input' y coloca su
//       decodificación RC4 en 'output' usando 'key' como clave.
//       Retorna 0 en caso de éxito, 1 caso contrario.
int _rc4Decode(const char *input, size_t length, char *output, size_t buff_size,
               const char *key, CipherInfo *info);

static void _generateKeyStream(CipherInfo *info, char *key_stream, int length);

static void _encode(const char *input, char* output, const char *key,
                    int length);



void RC4CipherInit(RC4Cipher *rc4) {
    rc4->encode = &_rc4Encode;
    rc4->decode = &_rc4Decode;
}

EncryptFunc getRC4Encoding(RC4Cipher *rc4) {
    return rc4->encode;
}

EncryptFunc getRC4Decoding(RC4Cipher *rc4) {
    return rc4->decode;
}

void RC4CipherRelease(RC4Cipher *rc4) {
    //do nothing;
}


//---------------------------- Funciones privadas ----------------------------//

int _rc4Encode(const char *input, size_t length, char *output, size_t buff_size,
               const char *key, CipherInfo *info) {
    if (length+1 > buff_size){
        fprintf(stderr, "Error: tamaño insuficiente de buffer.");
        return INSUF_BUFF_SIZE;
    }
    char key_stream[MAX_INPUT_SIZE];
    memset(key_stream, 0, MAX_INPUT_SIZE);
    _generateKeyStream(info, key_stream, length);
    _encode(input, output, key_stream, length);
    return SUCCESS;
}

int _rc4Decode(const char *input, size_t length, char *output, size_t buff_size,
               const char *key, CipherInfo *info) {
    return _rc4Encode(input, length, output, buff_size, key, info);
}

static void _generateKeyStream(CipherInfo *info, char *key_stream, int length){
    int i = 0;
    int j = 0;
    for (int k=0; k<length; k++){
        i = (i + 1)%VOCAB_SIZE;
        j = (j + cipherInfoGetSVectorInIndex(info, i)) % VOCAB_SIZE;
        cipherInfoSwapSVector(info, i, j);
        int a = (cipherInfoGetSVectorInIndex(info, i) +
                cipherInfoGetSVectorInIndex(info, j)) % VOCAB_SIZE;
        key_stream[k] = (char)cipherInfoGetSVectorInIndex(info, a);
    }
}


static void _encode(const char *input, char* output, const char *key,
                    int length){
    for (int i = 0; i < length; i++) {
        output[i] = input[i] ^ key[i];
    }
}



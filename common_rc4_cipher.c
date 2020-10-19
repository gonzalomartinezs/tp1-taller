#include "common_rc4_cipher.h"
#include <string.h>
#include <stdio.h>

#define SUCCESS 0
#define INSUF_BUFF_SIZE -1
#define VECTOR_SIZE 256
#define VOCAB_SIZE 256
#define MAX_INPUT_SIZE 64

// Pre: el buffer size de 'output' es mayor o igual al de 'input'.
// Post: toma el mensaje de 'input' y coloca su codificación
//       RC4 en 'output' usando 'key' como clave.
//       Retorna 0 en caso de éxito, 1 caso contrario.
int _rc4Encode(const char *input, size_t length, char *output, size_t buff_size,
               const char *key, void *aux);

// Pre: el buffer size de 'output' es mayor o igual al de 'input'.
// Post: toma el mensaje codificado 'input' y coloca su
//       decodificación RC4 en 'output' usando 'key' como clave.
//       Retorna 0 en caso de éxito, 1 caso contrario.
int _rc4Decode(const char *input, size_t length, char *output, size_t buff_size,
               const char *key, void *aux);

static void _initializeS(int *S);
static void _initializeT(char *T, const char *key);
static void _KSA(int *S, char *T);
static void _PRGA(int *S, char *key_stream, int length);
static void _generateKeyStream(char* key_stream, const char *original_key,
                               int length);
static void _swap(int *vector, int i, int j);
static void _encode(const char *input, char* output, const char *key,
                    int length);



void RC4CipherInit(RC4Cipher *rc4) {
    rc4->encode = _rc4Encode;
    rc4->decode = _rc4Decode;
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
               const char *key, void *aux) {
    if (length+1 > buff_size){
        fprintf(stderr, "Error: tamaño insuficiente de buffer.");
        return INSUF_BUFF_SIZE;
    }

    char key_stream[MAX_INPUT_SIZE];
    memset(key_stream, 0, MAX_INPUT_SIZE);
    _generateKeyStream(key_stream, key, length);
    _encode(input, output, key_stream, length);
    return SUCCESS;
}

int _rc4Decode(const char *input, size_t length, char *output, size_t buff_size,
               const char *key, void *aux) {
    return _rc4Encode(input, length, output, buff_size, key, aux);
}


static void _initializeS(int *S){
    for (int i=0; i<VECTOR_SIZE; i++){
        S[i] = i;
    }
}

static void _initializeT(char *T, const char *key){
    int length = (int)strlen(key);
    for (int i=0; i<VECTOR_SIZE; i++){
        T[i] = key[i%length];
    }
}

static void _KSA(int *S, char *T){
    int i = 0;
    for (int j=0; j<VECTOR_SIZE; j++){
        i = (i + S[j] + T[j])%VECTOR_SIZE;
        _swap(S, i, j);
    }
}

static void _PRGA(int *S, char *key_stream, int length){
    int i = 0;
    int j = 0;
    for (int k=0; k<length; k++){
        i = (i + 1)%VOCAB_SIZE;
        j = (j + S[i])%VOCAB_SIZE;
        _swap(S, i, j);
        int a =  (S[i] + S[j])%VOCAB_SIZE;
        key_stream[k] = (char)S[a];
    }
}

static void _generateKeyStream(char* key_stream,
                               const char *original_key, int length){
    int S_vector[VECTOR_SIZE];
    char T_vector[VECTOR_SIZE];
    _initializeS(S_vector);
    _initializeT(T_vector, original_key);
    _KSA(S_vector, T_vector);
    _PRGA(S_vector, key_stream, length);
}

static void _encode(const char *input, char* output, const char *key,
                    int length){
    for (int i = 0; i < length; i++) {
        output[i] = input[i] ^ key[i];
    }
}


static void _swap(int *vector, int i, int j){
    int aux = vector[i];
    vector[i] = vector[j];
    vector[j] = aux;
}

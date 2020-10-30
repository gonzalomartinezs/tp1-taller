#include "common_rc4_cipher.h"
#include <string.h>
#include <stdio.h>

#define SUCCESS 0
#define INSUF_BUFF_SIZE -1
#define VOCAB_SIZE 256
#define MAX_INPUT_SIZE 64

// Deja el vector S lsito para la ejecución del algoritmo RC4.
static void _KSA(RC4Cipher* rc4, const char* key);

// Genera la clave dinámica de tamanio 'length' a utilizar durante el cifrado
// cargandola en 'key_stream'
static void _generateKeyStream(RC4Cipher *rc4, char *key_stream, int length);

// Codifica el 'input' utilizando la 'key' y coloca el resultado en 'output'.
static void _encode(const char *input, char* output, const char *key,
                    int length);

// Intercamabia los valores del vector en los indices i y j.
static void _swap(int* vector, int i, int j);


void rc4CipherInit(RC4Cipher *rc4, const char* key) {
    rc4->key = key;
    rc4->index_1 = 0;
    rc4->index_2 = 0;
    for (int i=0; i<VECTOR_SIZE; i++){
        rc4->S[i] = i;
    }
    _KSA(rc4, key);
}

int rc4CipherEncode(RC4Cipher* rc4, const char *input, size_t length,
                    char *output, size_t buff_size) {
    if (length+1 > buff_size){
        fprintf(stderr, "Error: tamaño insuficiente de buffer.");
        return INSUF_BUFF_SIZE;
    }
    char key_stream[MAX_INPUT_SIZE];
    memset(key_stream, 0, MAX_INPUT_SIZE);
    _generateKeyStream(rc4, key_stream, length);
    _encode(input, output, key_stream, length);
    return SUCCESS;
}

int rc4CipherDecode(RC4Cipher* rc4, const char *input, size_t length,
                    char *output, size_t buff_size){
    return rc4CipherEncode(rc4, input, length, output, buff_size);
}

void rc4CipherRelease(RC4Cipher *rc4) {
    //do nothing;
}


//---------------------------- Funciones privadas ----------------------------//

static void _KSA(RC4Cipher* rc4, const char* key){
    int key_length = (int)strlen(key);
    if (key_length != 0) {
        int i = 0;
        for (int j = 0; j < VECTOR_SIZE; j++) {
            i = (i + rc4->S[j] + key[j%key_length]) % VECTOR_SIZE;
            _swap(rc4->S, i, j);
        }
    }
}

static void _generateKeyStream(RC4Cipher *rc4, char *key_stream, int length){
    int i = rc4->index_1;
    int j = rc4->index_2;
    for (int k=0; k<length; k++){
        i = (i + 1)%VOCAB_SIZE;
        j = (j + rc4->S[i]) % VOCAB_SIZE;
        _swap(rc4->S, i, j);
        int a = (rc4->S[i] + rc4->S[j]) % VOCAB_SIZE;
        key_stream[k] = (char)(rc4->S[a]);
    }
    rc4->index_1 = i;
    rc4->index_2 = j;
}


static void _encode(const char *input, char* output, const char *key,
                    int length){
    for (int i = 0; i < length; i++) {
        output[i] = input[i] ^ key[i];
    }
}

static void _swap(int* vector, int i, int j){
    int aux = vector[i];
    vector[i] = vector[j];
    vector[j] = aux;
}

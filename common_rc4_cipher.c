#include "common_rc4_cipher.h"
#include <string.h>
#include <stdio.h>

#define SUCCESS 0
#define INSUF_BUFF_SIZE -1
#define MEM_ERROR 2
#define VECTOR_SIZE 256
#define VOCAB_SIZE 256

static void _initializeS(int *S);
static void _initializeT(char *T, char*key);
static void _KSA(int *S, char *T);
static void _PRGA(int *S, char *key_stream, int length);
static void _generateKeyStream(char* key_stream, char* original_key, int length);
static void _swap(int *vector, int i, int j);
static void _encode(const char *input, char* output, char* key, int length);


int rc4Encode(const char *input, char *output, size_t buff_size, char *key) {
    int length = (int)strlen(input);

    if (length+1 > buff_size){
        fprintf(stderr, "Error: tamaño insuficiente de buffer.");
        return INSUF_BUFF_SIZE;
    }

    char* key_stream = (char*)malloc(sizeof(char)*strlen(input)+1);
    if (key_stream == NULL) {
        return MEM_ERROR;
    } else {
        _generateKeyStream(key_stream, key, length);
        _encode(input, output, key_stream, length);
        free(key_stream);
        return SUCCESS;
    }
}

int rc4Decode(const char *input, char *output, size_t buff_size, char *key) {
    return rc4Encode(input, output, buff_size, key);
}



//---------------------------- Funciones privadas ----------------------------//

static void _initializeS(int *S){
    for (int i=0; i<VECTOR_SIZE; i++){
        S[i] = i;
    }
}

static void _initializeT(char *T, char*key){
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
    int a;
    for (int k=0; k<length; k++){
        i = (i + 1)%VOCAB_SIZE;
        j = (j + S[i])%VOCAB_SIZE;
        _swap(S, i, j);
        a =  (S[i] + S[j])%VOCAB_SIZE;
        key_stream[k] = (char)S[a];
    }
}

static void _generateKeyStream(char* key_stream,
                               char* original_key, int length){
    int S_vector[VECTOR_SIZE];
    char T_vector[VECTOR_SIZE];
    _initializeS(S_vector);
    _initializeT(T_vector, original_key);
    _KSA(S_vector, T_vector);
    _PRGA(S_vector, key_stream, length);
}

static void _encode(const char *input, char* output, char* key, int length){
    for (int i = 0; i < length; i++) {
        output[i] = input[i] ^ key[i];
    }
}


static void _swap(int *vector, int i, int j){

    int aux = vector[i];
    vector[i] = vector[j];
    vector[j] = aux;
}



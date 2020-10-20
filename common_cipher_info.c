#include "common_cipher_info.h"
#include <string.h>
#include <stdio.h>

#define RC4_METHOD "rc4"

static void _KSA(CipherInfo *info, const char *key);

void cipherInfoInit(CipherInfo *info, const char *method, const char *key) {
    info->pos_in_key = 0;
    info->S_indexes[0] = 0;
    info->S_indexes[1] = 0;
    if (strcmp(method, RC4_METHOD) == 0){
        for (int i=0; i<VECTOR_SIZE; i++){
            info->S[i] = i;
        }
        _KSA(info, key);
    } else {
        memset(info->S, 0, VECTOR_SIZE*sizeof(int));
    }
}

int cipherInfoGetPositionInKey(CipherInfo *info) {
    return info->pos_in_key;
}

void cipherInfoSetPositionInKey(CipherInfo *info, int position) {
    info->pos_in_key = position;
}

int cipherInfoGetSVectorInIndex(CipherInfo *info, int index) {
    return info->S[index];
}

void cipherInfoSwapSVector(CipherInfo *info, int index1, int index2) {
    int aux = info->S[index1];
    info->S[index1] = info->S[index2];
    info->S[index2] = aux;
}

void cipherInfoRelease(CipherInfo *info) {
    //do nothing
}

int *cipherInfoGetVectorSIndexes(CipherInfo *info) {
    return info->S_indexes;
}

void cipherInfoSetVectorSIndexes(CipherInfo *info, int index1, int index2) {
    info->S_indexes[0] = index1;
    info->S_indexes[1] = index2;
}

//---------------------------- Funciones privadas ----------------------------//

static void _KSA(CipherInfo *info, const char *key){
    int key_length = (int)strlen(key);
    if (key_length != 0) {
        int i = 0;
        for (int j = 0; j < VECTOR_SIZE; j++) {
            i = (i + info->S[j] + key[j%key_length]) % VECTOR_SIZE;
            cipherInfoSwapSVector(info, i, j);
        }
    }
}

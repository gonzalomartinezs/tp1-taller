#include "common_cipher_info.h"
#define ERROR -1

void cipherInfoInit(CipherInfo *info) {
    info->pos_in_key = 0;
    for (int i=0; i<VECTOR_SIZE; i++){
        info->S[i] = i;
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


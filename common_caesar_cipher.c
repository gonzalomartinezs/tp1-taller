#include "common_caesar_cipher.h"
#include <string.h>
#include <stdio.h>

#define SUCCESS 0
#define INSUF_BUFF_SIZE -1
#define VOCAB_SIZE 256

void caesarCipherInit(CaesarCipher *caesar, const char* key) {
    caesar->key = atoi(key);
}

int caesarCipherEncode(CaesarCipher* cipher, const char *input, size_t length,
                       char *output, size_t buff_size) {
    if (length+1 > buff_size){
        fprintf(stderr, "Error: tamaño insuficiente de buffer.");
        return INSUF_BUFF_SIZE;
    }
    for (int i=0; i<length; i++){
        output[i] = (char)((input[i]+(cipher->key))%VOCAB_SIZE);
    }
    return SUCCESS;
}


int caesarCipherDecode(CaesarCipher* cipher, const char *input, size_t length,
                       char *output, size_t buff_size) {
    if (length+1 > buff_size){
        fprintf(stderr, "Error: tamaño insuficiente de buffer.");
        return INSUF_BUFF_SIZE;
    }
    for (int i=0; i<length; i++){
        output[i] = (char)((input[i]-(cipher->key))%VOCAB_SIZE);
    }
    return SUCCESS;
}

void caesarCipherRelease(CaesarCipher *caesar) {
    //do nothing
}






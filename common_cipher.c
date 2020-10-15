#include "common_cipher.h"
#include "common_caesar_cipher.h"
#include "common_vigenere_cipher.h"
#include "common_rc4_cipher.h"

#include <stdio.h>
#include <string.h>

#define SUCCESS 0
#define ERROR -1

int cipherInit(Cipher *cipher, const char *method) {
    if (strcmp(method,"cesar")==0){
        cipher->encode = &caesarEncode;
        cipher->decode = &caesarDecode;
    } else if (strcmp(method,"vigenere")==0){
        cipher->encode = &vigenereEncode;
        cipher->decode = &vigenereDecode;
    } else if (strcmp(method,"rc4")==0){
        cipher->encode = &rc4Encode;
        cipher->decode = &rc4Decode;
    } else {
        fprintf(stderr, "Error: Método inválido\n");
        return ERROR;
    }
    return SUCCESS;
}

int cipherEncode(Cipher *cipher, const char *input, char *output,
                 size_t buff_size, void* key) {
    return cipher->encode(input,output,buff_size,key);
}

int cipherDecode(Cipher *cipher, const char *input, char *output,
                 size_t buff_size, void* key) {
    return cipher->decode(input,output,buff_size,key);
}

void cipherRelease(Cipher *cipher) {
    //do nothing
}

#include "common_cipher.h"
#include "common_caesar_cipher.h"
#include "common_vigenere_cipher.h"
#include "common_rc4_cipher.h"
#include <string.h>
#include <stdio.h>

#define SUCCESS 0
#define ERROR -1
#define VIGENERE_NAME "vigenere"
#define CAESAR_NAME "cesar"
#define RC4_NAME "rc4"


int cipherInit(Cipher *cipher, const char *method, const char *key) {
    if ((strcmp(method, CAESAR_NAME) == 0) || (strcmp(method, RC4_NAME) == 0)
        || (strcmp(method, VIGENERE_NAME) == 0)){
            rc4CipherInit(&cipher->rc4, key);
            caesarCipherInit(&cipher->caesar, key);
            vigenereCipherInit(&cipher->vigenere, key);
            strncpy(cipher->method, method, METHOD_LENGTH);
            return SUCCESS;
    }
    fprintf(stderr, "Error: método incorrecto\n");
    return ERROR;
}

int cipherEncode(Cipher *cipher, const char *input, size_t length, char *output,
                 size_t buff_size) {
    if (strcmp(cipher->method, RC4_NAME) == 0){
        return rc4CipherEncode(&cipher->rc4, input, length, output, buff_size);
    } else if (strcmp(cipher->method, CAESAR_NAME) == 0){
        return caesarCipherEncode(&cipher->caesar, input, length, output,
                                  buff_size);
    }
    return vigenereCipherEncode(&cipher->vigenere, input, length, output,
                                buff_size);
}

int cipherDecode(Cipher *cipher, const char *input, size_t length, char *output,
                 size_t buff_size) {
    if (strcmp(cipher->method, RC4_NAME) == 0){
        return rc4CipherDecode(&cipher->rc4, input, length, output, buff_size);
    } else if (strcmp(cipher->method, CAESAR_NAME) == 0){
        return caesarCipherDecode(&cipher->caesar, input, length, output,
                                  buff_size);
    }
    return vigenereCipherDecode(&cipher->vigenere, input, length, output,
                                buff_size);
}

void cipherRelease(Cipher *cipher) {
    vigenereCipherRelease(&cipher->vigenere);
    caesarCipherRelease(&cipher->caesar);
    rc4CipherRelease(&cipher->rc4);
}

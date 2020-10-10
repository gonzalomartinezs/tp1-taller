#include "vigenere_cipher.h"
#include <string.h>
#include <stdio.h>

#define SUCCESS 0
#define INSUF_BUFF_SIZE 1
#define VOCAB_SIZE 256

char* extend_key (char* key, int length);

int vigenere_encode (char *input, char *output, size_t buff_size, char* key) {
    int length = (int)strlen(input);
    if (length+1 > buff_size){
        return INSUF_BUFF_SIZE;
    }
    char* extended_key = extend_key(key, length);
    for (int i=0; i<length; i++){
        output[i] = (char)((input[i]+extended_key[i])%VOCAB_SIZE);
    }
    output[length] = '\0';
    free(extended_key);
    return SUCCESS;
}


int vigenere_decode (char *input, char *output, size_t buff_size, char* key) {
    int length = (int)strlen(input);
    if (length+1 > buff_size){
        return INSUF_BUFF_SIZE;
    }
    char* extended_key = extend_key(key, length);
    for (int i=0; i<length; i++){
        output[i] = (char)((input[i]-extended_key[i])%VOCAB_SIZE);
    }
    output[length] = '\0';
    free(extended_key);
    return SUCCESS;
}


char* extend_key (char* key, int length){
    int key_length = strlen(key);
    char* extended_key = (char*)malloc((length+1)-sizeof(char));

    for (int i=0; i<length; i++){
        extended_key[i] = key[i%key_length];
    }
    return extended_key;
}
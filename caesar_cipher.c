#include "caesar_cipher.h"
#include <string.h>
#define SUCCESS 0
#define VOCAB_SIZE 256
#define INSUF_BUFF_SIZE 1

int caesar_encode(char* input, char* output, size_t buff_size, int key){
    int length = (int)strlen(input);
    if (length+1 > buff_size){
        return INSUF_BUFF_SIZE;
    }
    for (int i=0; i<length; i++){
        output[i] = (char)((input[i]+key)%VOCAB_SIZE);
    }
    output[length] = '\0';
    return SUCCESS;
}


int caesar_decode(char* input, char* output, size_t buff_size, int key){
    int length = (int)strlen(input);
    if (length+1 > buff_size){
        return INSUF_BUFF_SIZE;
    }
    for (int i=0; i<length; i++){
        output[i] = (char)((input[i]-key)%VOCAB_SIZE);
    }
    output[length] = '\0';
    return SUCCESS;
}

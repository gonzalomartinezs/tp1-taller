#ifndef TP1_COMMON_VIGENERE_CIPHER_H
#define TP1_COMMON_VIGENERE_CIPHER_H
#include <stdlib.h>
#include "common_cipher.h"

// Los artibutos son privados
typedef struct{
    EncryptFunc encode;
    EncryptFunc decode;
}VigenereCipher;

// Inicializa el cifrador.
void vigenereCipherInit(VigenereCipher* vigenere);

// Retorna un puntero a la función de encriptación Vigenere
EncryptFunc getVigenereEncoding(VigenereCipher* vigenere);

// Retorna un puntero a la función de desencriptación Vigenere
EncryptFunc getVigenereDecoding(VigenereCipher* vigenere);

// Libera los recursos del cifrador.
void vigenereCipherRelease(VigenereCipher* vigenere);


#endif //TP1_COMMON_VIGENERE_CIPHER_H

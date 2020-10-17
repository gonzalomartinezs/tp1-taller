#ifndef TP1_COMMON_CAESAR_CIPHER_H
#define TP1_COMMON_CAESAR_CIPHER_H

#include <stdlib.h>
#include "common_cipher.h"

typedef struct{
    EncryptFunc encode;
    EncryptFunc decode;
}CaesarCipher;

// Inicializa el cifrador.
void caesarCipherInit(CaesarCipher* caesar);

// Retorna un puntero a la función de encriptación Caesar
EncryptFunc getCaesarEncoding(CaesarCipher* caesar);

// Retorna un puntero a la función de desencriptación Caesar
EncryptFunc getCaesarDecoding(CaesarCipher* caesar);

// Libera los recursos del cifrador.
void caesarCipherRelease(CaesarCipher* caesar);

#endif
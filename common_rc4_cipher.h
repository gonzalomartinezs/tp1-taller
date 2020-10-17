#ifndef TP1_COMMON_RC4_CIPHER_H
#define TP1_COMMON_RC4_CIPHER_H
#include <stdlib.h>
#include "common_cipher.h"

typedef struct{
    EncryptFunc encode;
    EncryptFunc decode;
}RC4Cipher;

// Inicializa el cifrador.
void RC4CipherInit(RC4Cipher* rc4);

// Retorna un puntero a la función de encriptación rc4
EncryptFunc getRC4Encoding(RC4Cipher* rc4);

// Retorna un puntero a la función de desencriptación rc4
EncryptFunc getRC4Decoding(RC4Cipher* rc4);

// Libera los recursos del cifrador.
void RC4CipherRelease(RC4Cipher* rc4);

#endif //TP1_COMMON_RC4_CIPHER_H

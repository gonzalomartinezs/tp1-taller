#ifndef TP1_COMMON_CIPHER_H
#define TP1_COMMON_CIPHER_H
#include <stdlib.h>
#include "common_caesar_cipher.h"
#include "common_vigenere_cipher.h"
#include "common_rc4_cipher.h"

#define METHOD_LENGTH 20

// Los artibutos son privados
typedef struct {
    char method[METHOD_LENGTH];
    CaesarCipher caesar;
    VigenereCipher vigenere;
    RC4Cipher rc4;
}Cipher;

// Inicializa el cifrador de acuerdo al método recibido.
// Retorna 0 en caso de éxito y -1 si el método es inválido.
int cipherInit(Cipher *cipher, const char *method, const char *key);

// Pre: el buffer size de 'output' es mayor o igual al de 'input'.
// Post: toma el mensaje codificado 'input' y coloca su
//       codificación en 'output'.
//       Retorna 0 en caso de éxito, 1 caso contrario.
int cipherEncode(Cipher *cipher, const char *input, size_t length, char *output,
                 size_t buff_size);

// Pre: el buffer size de 'output' es mayor o igual al de 'input'.
// Post: toma el mensaje codificado 'input' y coloca su
//       decodificación en 'output'.
//       Retorna 0 en caso de éxito, 1 caso contrario.
int cipherDecode(Cipher *cipher, const char *input, size_t length, char *output,
             size_t buff_size);

// Libera los recursos utilizados por el cifrador.
void cipherRelease(Cipher* cipher);

#endif

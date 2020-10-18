#ifndef TP1_COMMON_CIPHER_H
#define TP1_COMMON_CIPHER_H
#include <stdlib.h>

#define METHOD_LENGTH 10

typedef int (*EncryptFunc)(const char* input, size_t length, char* output,
                            size_t buff_size, const char *key);

typedef struct {
    EncryptFunc encode;
    EncryptFunc decode;
}Cipher;

// Inicializa el cifrador de acuerdo al método recibido.
// Retorna 0 en caso de éxito y -1 si el método es inválido.
int cipherInit(Cipher* cipher, const char* method);

// Pre: el buffer size de 'output' es mayor o igual al de 'input'.
// Post: toma el mensaje codificado 'input' y coloca su
//       codificación en 'output' usando 'key' como clave.
//       Retorna 0 en caso de éxito, 1 caso contrario.
int cipherEncode(Cipher *cipher, const char *input, size_t length, char *output,
                 size_t buff_size, const char *key);

// Pre: el buffer size de 'output' es mayor o igual al de 'input'.
// Post: toma el mensaje codificado 'input' y coloca su
//       decodificación en 'output' usando 'key' como clave.
//       Retorna 0 en caso de éxito, 1 caso contrario.
int cipherDecode(Cipher *cipher, const char *input, size_t length, char *output,
             size_t buff_size, const char *key);

// Libera los recursos utilizados por el cifrador.
void cipherRelease(Cipher* cipher);

#endif

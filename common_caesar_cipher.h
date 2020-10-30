#ifndef TP1_COMMON_CAESAR_CIPHER_H
#define TP1_COMMON_CAESAR_CIPHER_H

#include <stdlib.h>

// Los artibutos son privados
typedef struct{
    int key;
}CaesarCipher;

// Inicializa el cifrador.
void caesarCipherInit(CaesarCipher* caesar, const char* key);

// Pre: el buffer size de 'output' es mayor o igual al de 'input'.
// Post: toma el mensaje de 'input' y coloca su codificación
//       Cesar en 'output' usando 'key' como clave.
//       Retorna 0 en caso de éxito, 1 caso contrario.
int caesarCipherEncode(CaesarCipher* cipher, const char *input, size_t length,
                        char *output, size_t buff_size);

// Pre: el buffer size de 'output' es mayor o igual al de 'input'.
// Post: toma el mensaje codificado 'input' y coloca su
//       decodificación Cesar en 'output' usando 'key' como clave.
//       Retorna 0 en caso de éxito, 1 caso contrario.
int caesarCipherDecode(CaesarCipher* cipher, const char *input, size_t length,
                        char *output, size_t buff_size);

// Libera los recursos del cifrador.
void caesarCipherRelease(CaesarCipher* caesar);

#endif

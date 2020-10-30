#ifndef TP1_COMMON_RC4_CIPHER_H
#define TP1_COMMON_RC4_CIPHER_H
#include <stdlib.h>

#define VECTOR_SIZE 256

// Los artibutos son privados
typedef struct {
    const char* key;
    int S[VECTOR_SIZE];
    int index_1;
    int index_2;
}RC4Cipher;


// Inicializa el cifrador.
void rc4CipherInit(RC4Cipher* rc4, const char* key);

// Pre: el buffer size de 'output' es mayor o igual al de 'input'.
// Post: toma el mensaje de 'input' y coloca su codificación
//       RC4 en 'output' usando 'key' como clave.
//       Retorna 0 en caso de éxito, 1 caso contrario.
int rc4CipherEncode(RC4Cipher* rc4, const char *input, size_t length,
                    char *output, size_t buff_size);

// Pre: el buffer size de 'output' es mayor o igual al de 'input'.
// Post: toma el mensaje codificado 'input' y coloca su
//       decodificación RC4 en 'output' usando 'key' como clave.
//       Retorna 0 en caso de éxito, 1 caso contrario.
int rc4CipherDecode(RC4Cipher* rc4, const char *input, size_t length,
                    char *output, size_t buff_size);

// Libera los recursos del cifrador.
void rc4CipherRelease(RC4Cipher* rc4);

#endif //TP1_COMMON_RC4_CIPHER_H

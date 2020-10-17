#ifndef TP1_COMMON_CAESAR_CIPHER_H
#define TP1_COMMON_CAESAR_CIPHER_H

#include <stdlib.h>

// Pre: el buffer size de 'output' es mayor o igual al de 'input'.
// Post: toma el mensaje de 'input' y coloca su codificación
//       Cesar en 'output' usando 'key' como clave.
//       Retorna 0 en caso de éxito, 1 caso contrario.
int caesarEncode(const char *input, char* output, size_t buff_size, const char *key);

// Pre: el buffer size de 'output' es mayor o igual al de 'input'.
// Post: toma el mensaje codificado 'input' y coloca su
//       decodificación Cesar en 'output' usando 'key' como clave.
//       Retorna 0 en caso de éxito, 1 caso contrario.
int caesarDecode(const char *input, char* output, size_t buff_size, const char *key);

#endif
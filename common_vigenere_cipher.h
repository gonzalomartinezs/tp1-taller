#ifndef TP1_COMMON_VIGENERE_CIPHER_H
#define TP1_COMMON_VIGENERE_CIPHER_H
#include <stdlib.h>

// Los artibutos son privados
typedef struct{
    const char* key;
    int position_in_key;
}VigenereCipher;

// Inicializa el cifrador.
void vigenereCipherInit(VigenereCipher* vigenere, const char* key);

// Pre: el buffer size de 'output' es mayor o igual al de 'input'.
// Post: toma el mensaje de 'input' y coloca su codificación
//       Vigenere en 'output' usando 'key' como clave.
//       Retorna 0 en caso de éxito, 1 caso contrario.
int vigenereCipherEncode(VigenereCipher* vigenere, const char *input,
                         size_t length, char *output, size_t buff_size);

// Pre: el buffer size de 'output' es mayor o igual al de 'input'.
// Post: toma el mensaje codificado 'input' y coloca su
//       decodificación Vigenere en 'output' usando 'key' como clave.
//       Retorna 0 en caso de éxito, 1 caso contrario.
int vigenereCipherDecode(VigenereCipher* vigenere, const char *input,
                         size_t length, char *output, size_t buff_size);

// Libera los recursos del cifrador.
void vigenereCipherRelease(VigenereCipher* vigenere);


#endif //TP1_COMMON_VIGENERE_CIPHER_H

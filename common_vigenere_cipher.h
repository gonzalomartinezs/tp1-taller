#ifndef TP1_COMMON_VIGENERE_CIPHER_H
#define TP1_COMMON_VIGENERE_CIPHER_H
#include <stdlib.h>
#include "common_cipher.h"

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





// Pre: el buffer size de 'output' es mayor o igual al de 'input'.
// Post: toma el mensaje de 'input' y coloca su codificación
//       Vigenere en 'output' usando 'key' como clave.
//       Retorna 0 en caso de éxito, 1 caso contrario.
int _vigenereEncode(const char *input, size_t length, char *output,
                    size_t buff_size, const char *key);

// Pre: el buffer size de 'output' es mayor o igual al de 'input'.
// Post: toma el mensaje codificado 'input' y coloca su
//       decodificación Vigenere en 'output' usando 'key' como clave.
//       Retorna 0 en caso de éxito, 1 caso contrario.
int _vigenereDecode(const char *input, size_t length, char *output,
                    size_t buff_size, const char *key);


#endif //TP1_COMMON_VIGENERE_CIPHER_H

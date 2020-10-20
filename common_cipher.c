#include "common_cipher.h"
#include "common_caesar_cipher.h"
#include "common_vigenere_cipher.h"
#include "common_rc4_cipher.h"

#include <stdio.h>
#include <string.h>

#define VIGENERE_NAME "vigenere"
#define CAESAR_NAME "cesar"
#define RC4_NAME "rc4"

// Asigna a 'cipher' las funciones de codificación y decodificación del método
// Caesar.
static void _initializeWithCaesar(Cipher *cipher);

// Asigna a 'cipher' las funciones de codificación y decodificación del método
// Vigenere.
static void _initializeWithVigenere(Cipher *cipher);

// Asigna a 'cipher' las funciones de codificación y decodificación del método
// RC4.
static void _initializeWithRC4(Cipher *cipher);



int cipherInit(Cipher *cipher, const char *method, const char *key) {
    if (strcmp(method,CAESAR_NAME)==0){
        _initializeWithCaesar(cipher);
    } else if (strcmp(method,VIGENERE_NAME)==0){
        _initializeWithVigenere(cipher);
    } else if (strcmp(method,RC4_NAME)==0){
        _initializeWithRC4(cipher);
    } else {
        fprintf(stderr, "Error: Método inválido\n");
        return ERROR;
    }
    CipherInfo info;
    cipherInfoInit(&info, method, key);
    cipher->info = info;
    return SUCCESS;
}

int cipherEncode(Cipher *cipher, const char *input, size_t length, char *output,
                 size_t buff_size, const char *key) {
    return cipher->encode(input, length, output, buff_size, key,
                          &(cipher->info));
}

int cipherDecode(Cipher *cipher, const char *input, size_t length, char *output,
                 size_t buff_size, const char *key) {
    return cipher->decode(input, length, output, buff_size, key,
                          &(cipher->info));
}

void cipherRelease(Cipher *cipher) {
    cipherInfoRelease(&(cipher->info));
}


//---------------------------- Funciones privadas ----------------------------//

static void _initializeWithCaesar(Cipher *cipher) {
    CaesarCipher caesar;
    caesarCipherInit(&caesar);
    cipher->encode = getCaesarEncoding(&caesar);
    cipher->decode = getCaesarDecoding(&caesar);
    caesarCipherRelease(&caesar);
}

static void _initializeWithVigenere(Cipher *cipher) {
    VigenereCipher vigenere;
    vigenereCipherInit(&vigenere);
    cipher->encode = getVigenereEncoding(&vigenere);
    cipher->decode = getVigenereDecoding(&vigenere);
    vigenereCipherRelease(&vigenere);
}

static void _initializeWithRC4(Cipher *cipher) {
    RC4Cipher rc4;
    RC4CipherInit(&rc4);
    cipher->encode = getRC4Encoding(&rc4);
    cipher->decode = getRC4Decoding(&rc4);
    RC4CipherRelease(&rc4);
}

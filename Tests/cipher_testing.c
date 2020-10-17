#include <stdio.h>
#include <string.h>
#include "../common_cipher.h"
#include "testing.h"
#define CAESAR_METHOD "cesar"
#define SUCCESS 0
#define ERROR -1

void casoBasicoDeEncriptacionCaesar(Tester* tester){

    Cipher cipher;
    cipherInit(&cipher,CAESAR_METHOD);
    printf("Prueba %i: Encripto 'ABCD' con key=5, obtengo 'FGHI'\n",
           tester->pruebas);
    char string_prueba[] = "ABCD";
    char string_codif[5];
    int encoding = cipherEncode(&cipher, string_prueba, strlen(string_prueba),
                                string_codif, sizeof(string_codif), "5");

    if (encoding == SUCCESS){
        testerEqualStrings("FGHI", string_codif, tester);
    } else {
        testerNotifyError(encoding);
    }
}

void casoBasicoDeDesencriptacionCaesar(Tester* tester){

    Cipher cipher;
    cipherInit(&cipher,CAESAR_METHOD);
    printf("Prueba %i: Desencripto 'FGHI' con key=5, obtengo 'ABCD'\n",
           tester->pruebas);
    char string_prueba[] = "FGHI";
    char string_codif[5];
    int decoding = cipherDecode(&cipher, string_prueba, strlen(string_prueba),
                                string_codif, sizeof(string_codif), "5");

    if (decoding == SUCCESS){
        testerEqualStrings("ABCD", string_codif, tester);
    } else {
        testerNotifyError(decoding);
    }
}

void encriptoYDesencriptoConCaesarObtengoMismoValor(Tester* tester){

    Cipher cipher;
    cipherInit(&cipher,CAESAR_METHOD);
    printf("Prueba %i: Encripto y desencripto 'ABCD' con key=10, obtengo 'ABCD'\n",
           tester->pruebas);
    char string_prueba[] = "ABCD";
    char string_codif[5];

    int encoding = cipherEncode(&cipher, string_prueba, strlen(string_prueba),
                                string_codif, sizeof(string_codif), "10");
    int decoding = cipherDecode(&cipher, string_codif, strlen(string_codif),
                                string_codif, sizeof(string_codif), "10");

    if ((encoding == SUCCESS) && (decoding == SUCCESS)){
        testerEqualStrings("ABCD", string_codif, tester);
    } else {
        (encoding == ERROR) ? testerNotifyError(encoding) : NULL;
        (decoding == ERROR) ? testerNotifyError(decoding) : NULL;
    }
}

void encriptacionCaesarConKey256(Tester* tester){

    Cipher cipher;
    cipherInit(&cipher,CAESAR_METHOD);
    printf("Prueba %i: Encripto 'ABCD' con key=256, obtengo 'ABCD'\n",
           tester->pruebas);
    char string_prueba[] = "ABCD";
    char string_codif[5];
    int encoding = cipherEncode(&cipher, string_prueba, strlen(string_prueba), string_codif,
                                sizeof(string_codif), "256");

    if (encoding == SUCCESS){
        testerEqualStrings("ABCD", string_codif, tester);
    } else {
        testerNotifyError(encoding);
    }
}

void desencriptacionCaesarConKey256(Tester* tester){

    Cipher cipher;
    cipherInit(&cipher,CAESAR_METHOD);
    printf("Prueba %i: Desencripto 'FGHI' con key=256, obtengo 'FGHI'\n",
           tester->pruebas);
    char string_prueba[] = "FGHI";
    char string_codif[5];
    int decoding = cipherDecode(&cipher, string_prueba, strlen(string_prueba), string_codif,
                                sizeof(string_codif), "256");

    if (decoding == SUCCESS){
        testerEqualStrings("FGHI", string_codif, tester);
    } else {
        testerNotifyError(decoding);
    }
}

void encriptacionCaesarConBufferInsuficiente(Tester* tester){

    Cipher cipher;
    cipherInit(&cipher,CAESAR_METHOD);
    printf("Prueba %i: Intento encriptar en buffer insuficiente, obtengo error\n",
           tester->pruebas);
    char string_prueba[] = "FGHI";
    char string_codif[2];
    int encoding = cipherEncode(&cipher, string_prueba, strlen(string_prueba), string_codif,
                                sizeof(string_codif), "256");
    testerEqualInts(ERROR, encoding, tester);
}

void desencriptacionCaesarConBufferInsuficiente(Tester* tester){

    Cipher cipher;
    cipherInit(&cipher,CAESAR_METHOD);
    printf("Prueba %i: Intento desencriptar en buffer insuficiente, obtengo error\n",
           tester->pruebas);
    char string_prueba[] = "FGHI";
    char string_codif[2];
    int decoding = cipherDecode(&cipher, string_prueba, strlen(string_prueba), string_codif,
                                sizeof(string_codif), "256");

    testerEqualInts(ERROR, decoding, tester);
}

int main(){
    Tester tester;
    testerCreate(&tester);

    casoBasicoDeEncriptacionCaesar(&tester);
    casoBasicoDeDesencriptacionCaesar(&tester);
    encriptoYDesencriptoConCaesarObtengoMismoValor(&tester);
    encriptacionCaesarConKey256(&tester);
    desencriptacionCaesarConKey256(&tester);
    encriptacionCaesarConBufferInsuficiente(&tester);
    desencriptacionCaesarConBufferInsuficiente(&tester);

    testerSummarize(&tester);
    testerDestroy(&tester);
    return 0;
}
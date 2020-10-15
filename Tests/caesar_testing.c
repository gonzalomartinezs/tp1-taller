#include <stdio.h>
#include "../common_caesar_cipher.h"
#include "testing.h"
#define SUCCESS 0
#define ERROR 1

void casoBasicoDeEncriptacionCaesar(Tester *tester){

    printf("Prueba %i: Encripto 'ABCD' con key=5, obtengo 'FGHI'\n",
           tester->pruebas);
    char string_prueba[] = "ABCD";
    char string_codif[5];
    int encoding = caesarEncode(string_prueba, string_codif, sizeof(string_codif), 5);

    if (encoding == SUCCESS){
        tester_equal_strings("FGHI", string_codif, tester);
    } else {
        tester_notify_error(encoding);
    }
}

void casoBasicoDeDesencriptacionCaesar(Tester *tester){

    printf("Prueba %i: Desencripto 'FGHI' con key=5, obtengo 'ABCD'\n",
           tester->pruebas);
    char string_prueba[] = "FGHI";
    char string_codif[5];
    int decoding = caesarDecode(string_prueba, string_codif, sizeof(string_codif), 5);

    if (decoding == SUCCESS){
        tester_equal_strings("ABCD", string_codif, tester);
    } else {
        tester_notify_error(decoding);
    }
}

void encriptoYDesencriptoConCaesarObtengoMismoValor(Tester *tester){
    printf("Prueba %i: Encripto y desencripto 'ABCD' con key=10, obtengo 'ABCD'\n",
           tester->pruebas);
    char string_prueba[] = "ABCD";
    char string_codif[5];

    int encoding = caesarEncode(string_prueba, string_codif, sizeof(string_codif), 10);
    int decoding = caesarDecode(string_codif, string_codif, sizeof(string_codif), 10);

    if ((encoding == SUCCESS) & (decoding == SUCCESS)){
        tester_equal_strings("ABCD", string_codif, tester);
    } else {
        (encoding == ERROR)?tester_notify_error(encoding):NULL;
        (decoding == ERROR)?tester_notify_error(decoding):NULL;
    }
}

void encriptacionCaesarConKey256(Tester *tester){

    printf("Prueba %i: Encripto 'ABCD' con key=256, obtengo 'ABCD'\n",
           tester->pruebas);
    char string_prueba[] = "ABCD";
    char string_codif[5];
    int encoding = caesarEncode(string_prueba, string_codif, sizeof(string_codif), 256);

    if (encoding == SUCCESS){
        tester_equal_strings("ABCD", string_codif, tester);
    } else {
        tester_notify_error(encoding);
    }
}

void desencriptacionCaesarConKey256(Tester *tester){

    printf("Prueba %i: Desencripto 'FGHI' con key=256, obtengo 'FGHI'\n",
           tester->pruebas);
    char string_prueba[] = "FGHI";
    char string_codif[5];
    int decoding = caesarDecode(string_prueba, string_codif, sizeof(string_codif), 256);

    if (decoding == SUCCESS){
        tester_equal_strings("FGHI", string_codif, tester);
    } else {
        tester_notify_error(decoding);
    }
}

void encriptacionCaesarConBufferInsuficiente(Tester *tester){
    printf("Prueba %i: Intento encriptar en buffer insuficiente, obtengo error\n",
           tester->pruebas);
    char string_prueba[] = "FGHI";
    char string_codif[2];
    int encoding = caesarEncode(string_prueba, string_codif, sizeof(string_codif), 256);

    tester_equal_ints(ERROR, encoding, tester);
}

void desencriptacionCaesarConBufferInsuficiente(Tester *tester){
    printf("Prueba %i: Intento desencriptar en buffer insuficiente, obtengo error\n",
           tester->pruebas);
    char string_prueba[] = "FGHI";
    char string_codif[2];
    int decoding = caesarDecode(string_prueba, string_codif, sizeof(string_codif), 256);

    tester_equal_ints(ERROR, decoding, tester);
}

int main(){
    tester_t tester;
    tester_create(&tester);

    CasoBasicoDeEncriptacion(&tester);
    CasoBasicoDeDesencriptacion(&tester);
    EncriptoYDesencriptoObtengoMismoValor(&tester);
    EncriptacionConKey256(&tester);
    DesencriptacionConKey256(&tester);
    EncriptacionConBufferInsuficiente(&tester);
    DesencriptacionConBufferInsuficiente(&tester);

    tester_summarize(&tester);
    tester_destroy(&tester);
    return 0;
}
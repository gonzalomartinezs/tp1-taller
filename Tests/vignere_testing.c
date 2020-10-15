#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../common_vigenere_cipher.h"
#include "testing.h"
#define SUCCESS 0
#define ERROR 1

void casoBasicoDeEncriptacionCaesar(Tester *tester){

    printf("Prueba %i: Encripto 'AAA' con key='01', obtengo 'qrq'\n",
           tester->pruebas);

    char string_prueba[] = "AAA";
    int buff_size = (int)(strlen(string_prueba)*sizeof(char))+1;

    char* string_codif = (char*)malloc(buff_size);
    int encoding = vigenereEncode(string_prueba, string_codif, buff_size, "01");

    if (encoding == SUCCESS){
        tester_equal_strings("qrq", string_codif, tester);
    } else {
        tester_notify_error(encoding);
    }
    free(string_codif);
}

//void CasoBasicoDeDesencriptacion(tester_t* tester){
//
//    printf("Prueba %i: Desencripto 'FGHI' con key=5, obtengo 'ABCD'\n",
//           tester->pruebas);
//    char string_prueba[] = "FGHI";
//    char string_codif[5];
//    int decoding = vigenereDecode(string_prueba, string_codif, sizeof(string_codif), 5);
//
//    if (decoding == SUCCESS){
//        tester_equal_strings("ABCD", string_codif, tester);
//    } else {
//        tester_notify_error(decoding);
//    }
//}
//
void encriptoYDesencriptoConCaesarObtengoMismoValor(Tester *tester){
    printf("Prueba %i: Encripto y desencripto '¡Vigenère!' con key='Holã!', obtengo '¡Vigenère!'\n",
           tester->pruebas);
    char string_prueba[] = "¡Vigenère!";
    int buff_size = (int)(strlen(string_prueba)*sizeof(char))+1;
    char* string_codif = (char*)malloc(buff_size);

    int encoding = vigenereEncode(string_prueba, string_codif, buff_size,
                                  "Holã!");
    int decoding = vigenereDecode(string_codif, string_codif, buff_size,
                                  "Holã!");

    if ((encoding == SUCCESS) & (decoding == SUCCESS)){
        tester_equal_strings("¡Vigenère!", string_codif, tester);
    } else {
        (encoding == ERROR)?tester_notify_error(encoding):NULL;
        (decoding == ERROR)?tester_notify_error(decoding):NULL;
    }
}
//
//void EncriptacionConKey256(tester_t* tester){
//
//    printf("Prueba %i: Encripto 'ABCD' con key=256, obtengo 'ABCD'\n",
//           tester->pruebas);
//    char string_prueba[] = "ABCD";
//    char string_codif[5];
//    int encoding = vigenereEncode(string_prueba, string_codif, sizeof(string_codif), 256);
//
//    if (encoding == SUCCESS){
//        tester_equal_strings("ABCD", string_codif, tester);
//    } else {
//        tester_notify_error(encoding);
//    }
//}
//
//void DesencriptacionConKey256(tester_t* tester){
//
//    printf("Prueba %i: Desencripto 'FGHI' con key=256, obtengo 'FGHI'\n",
//           tester->pruebas);
//    char string_prueba[] = "FGHI";
//    char string_codif[5];
//    int decoding = vigenereDecode(string_prueba, string_codif, sizeof(string_codif), 256);
//
//    if (decoding == SUCCESS){
//        tester_equal_strings("FGHI", string_codif, tester);
//    } else {
//        tester_notify_error(decoding);
//    }
//}
//
//void EncriptacionConBufferInsuficiente(tester_t* tester){
//    printf("Prueba %i: Intento encriptar en buffer insuficiente, obtengo error\n",
//           tester->pruebas);
//    char string_prueba[] = "FGHI";
//    char string_codif[2];
//    int encoding = vigenereEncode(string_prueba, string_codif, sizeof(string_codif), 256);
//
//    tester_equal_ints(ERROR, encoding, tester);
//}
//
//void DesencriptacionConBufferInsuficiente(tester_t* tester){
//    printf("Prueba %i: Intento desencriptar en buffer insuficiente, obtengo error\n",
//           tester->pruebas);
//    char string_prueba[] = "FGHI";
//    char string_codif[2];
//    int decoding = vigenereDecode(string_prueba, string_codif, sizeof(string_codif), 256);
//
//    tester_equal_ints(ERROR, decoding, tester);
//}

int main(){
    tester_t tester;
    tester_create(&tester);

//    CasoBasicoDeEncriptacion(&tester);
//    CasoBasicoDeDesencriptacion(&tester);
    EncriptoYDesencriptoObtengoMismoValor(&tester);
//    EncriptacionConKey256(&tester);
//    DesencriptacionConKey256(&tester);
//    EncriptacionConBufferInsuficiente(&tester);
//    DesencriptacionConBufferInsuficiente(&tester);

    tester_summarize(&tester);
    tester_destroy(&tester);
    return 0;
}
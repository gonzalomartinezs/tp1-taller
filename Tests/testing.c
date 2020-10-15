#include "testing.h"
#include <string.h>
#include <stdio.h>

#define SUCCESS 0

int testerCreate(Tester* tester){
    tester->exitos = 0;
    tester->pruebas = 0;
    return SUCCESS;
}

int testerDestroy(Tester* tester){
    return SUCCESS;
}

void testerEqualInts(int expected, int obtained, Tester *tester) {
    if (expected == obtained){
        printf("\033[1;32mEXITO\033[0;0m\n");
        tester->exitos++;
    } else {
        printf("\033[1;31mFALLO: Se esperaba %i y se obtuvo %i\033[0;0m\n", expected, obtained);
    }
    tester->pruebas++;
}

void testerEqualStrings(char *expected, char *obtained, Tester *tester) {
    if (strcmp(expected,obtained)==0){
        printf("\033[1;32mEXITO\033[0;0m\n");
        tester->exitos++;
    } else {
        printf("\033[1;31mFALLO: Se esperaba '%s' y se obtuvo '%s'\033[0;0m\n", expected, obtained);
    }
    tester->pruebas++;
}

void testerEqualChars(char expected, char obtained, Tester *tester) {
    if (expected == obtained){
        printf("\033[1;32mEXITO\033[0;0m\n");
        tester->exitos++;
    } else {
        printf("\033[1;31mFALLO: Se esperaba '%c' y se obtuvo '%c'\033[0;0m\n", expected, obtained);
    }
    tester->pruebas++;
}

void testerEqualPointers(void *expected, void *obtained, Tester *tester) {
    if (expected == obtained){
        printf("\033[1;32mEXITO\033[0;0m\n");
        tester->exitos++;
    } else {
        printf("\033[1;31mFALLO: Se esperaba %p y se obtuvo %p\033[0;0m\n", expected, obtained);
    }
    tester->pruebas++;
}

void testerSummarize(Tester *tester) {
    printf("\nSe obtuvieron %i exitos en %i pruebas (%.2f%)",
           tester->exitos, tester->pruebas, ((float)tester->exitos/tester->pruebas)*100);
}

void testerNotifyError(int error_code) {
    printf("\033[1;31mCODIGO DE ERROR: %i.\033[0;0m\n", error_code);
}


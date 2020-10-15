#ifndef TP1_TESTING_H
#define TP1_TESTING_H

typedef struct{
    int exitos;
    int pruebas;
}Tester;

int testerCreate(Tester* tester);

int testerDestroy(Tester* tester);

void testerEqualInts(int expected, int obtained, Tester* tester);

void testerEqualStrings(char* expected, char* obtained, Tester* tester);

void testerEqualChars(char expected, char obtained, Tester* tester);

void testerEqualPointers(void* expected, void* obtained, Tester* tester);

void testerSummarize(Tester* tester);

void testerNotifyError(int error_code);

#endif //TP1_TESTING_H

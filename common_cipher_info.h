#ifndef TP1_COMMON_CIPHER_INFO_H
#define TP1_COMMON_CIPHER_INFO_H

#define VECTOR_SIZE 256
#define INDEXES_AMOUNT 2

typedef struct {
    int pos_in_key;
    int S[VECTOR_SIZE];
    int S_indexes[INDEXES_AMOUNT];
}CipherInfo;

// Inicializa la estructura con todos los valores en 0.
void cipherInfoInit(CipherInfo *info, const char *method, const char *key);

// Devuelve la próxima posición de la key que debe procesar el cifrador.
int cipherInfoGetPositionInKey(CipherInfo* info);

// Establece la próxima posición de la key que debe procesar el cifrador.
void cipherInfoSetPositionInKey(CipherInfo *info, int position);

// Devuelve el valor del vector S en el índice i.
int cipherInfoGetSVectorInIndex(CipherInfo* info, int index);

// Swapea en el vector S los valores de los índices recibidos.
void cipherInfoSwapSVector(CipherInfo* info, int index1, int index2);

// Retorna un puntero al array que contiene los índices del vector S.
int* cipherInfoGetVectorSIndexes(CipherInfo* info);

// Establece los índices utilizados por el vector S
void cipherInfoSetVectorSIndexes(CipherInfo* info, int index1, int index2);

// Libera los recursos del tda
void cipherInfoRelease(CipherInfo* info);

#endif //TP1_COMMON_CIPHER_INFO_H

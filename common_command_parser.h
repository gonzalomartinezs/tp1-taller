#ifndef TP1_COMMON_COMMAND_PARSER_H
#define TP1_COMMON_COMMAND_PARSER_H

// Pre: el 'buff_size' de 'method' es suficiente para almacenar
// el valor introducido.
// Extrae el método de codificación a emplear
void extract_method(char *argv_option, char *method, int buff_size);

// Pre: el 'buff_size' de 'key' es suficiente para almacenar
// el valor introducido.
// Extrae la key a emplear durante la codificación/decodificación
void extract_key(char *argv_option, char *key, int buff_size);
#endif //TP1_COMMON_COMMAND_PARSER_H

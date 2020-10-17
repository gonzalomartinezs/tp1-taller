#include "common_command_parser.h"
#include <string.h>
// Extrae la opcion introducida de 'argv_option' y la carga en 'option'
static void _extract(char *argv_option, char *option, int buff_size);

void extract_method(char *argv_option, char *method, int buff_size) {
    _extract(argv_option, method, buff_size);
}

void extract_key(char *argv_option, char *key, int buff_size) {
    _extract(argv_option, key, buff_size);
}


//---------------------------- Funciones privadas ----------------------------//
static void _extract(char *argv_option, char *option, int buff_size)
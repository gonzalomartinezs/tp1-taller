#ifndef TP1_COMMON_COMMAND_PARSER_H
#define TP1_COMMON_COMMAND_PARSER_H

#define HOST_SIZE 20
#define SERVICE_SIZE 10
#define METHOD_SIZE 20
#define KEY_SIZE 50

// Carga las opciones intrucidas por el usuario en los argumentos recibidos.
// Devuelve 0 en caso de éxito y -1 si el número de argumentos es incorrecto.
int commandParserClient(int argc, char** argv, char* host, char* service,
                        char* method, char* key);

// Carga las opciones intrucidas por el usuario en los argumentos recibidos.
// Devuelve 0 en caso de éxito y -1 si el número de argumentos es incorrecto.
int commandParserServer(int argc, char** argv, char* host, char* service,
                        char* key);

#endif //TP1_COMMON_COMMAND_PARSER_H

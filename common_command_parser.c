#include "common_command_parser.h"
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define ERROR -1
#define SUCCESS 0
#define CLIENT_ARGS_AMOUNT 5
#define SERVER_ARGS_AMOUNT 4
#define HOST_ARG 1
#define CL_SERVICE_ARG 2
#define SV_SERVICE_ARG 1

// Asigna las opciones introducidas a los parámetros.
// Devuelve 0 en caso de éxito y -1 si algún parámetro es incorrecto.
static int _parseClient(int argc, char **argv, char *host, char *service,
                        char *method, char *key);

// Asigna las opciones introducidas a los parámetros.
// Devuelve 0 en caso de éxito y -1 si algún parámetro es incorrecto.
static int _parseServer(int argc, char **argv, char *service, char *method,
                        char *key);

// Carga en 'option' la opción introducida por el usuario para dicho campo
static void _extractOption(const char *recv_option, char *option);

// Lee el 'method' y la 'key' introducidos por le usuario.
// Devuelve 0 en caso de éxito y -1 si algún parámetro es incorrecto.
static int _parseMethodAndKey(int argc, char **argv, char *method, char *key);



int commandParserClient(int argc, char **argv, char *host, char *service,
                        char *method, char *key) {
    if (argc != CLIENT_ARGS_AMOUNT){
        fprintf(stderr,"Cantidad de argumentos errónea.\n");
        return ERROR;
    }
    return _parseClient(argc, argv, host, service, method, key);
}

int commandParserServer(int argc, char **argv, char *host, char *service,
                        char *key) {
    if (argc != SERVER_ARGS_AMOUNT){
        fprintf(stderr,"Cantidad de argumentos errónea.\n");
        return ERROR;
    }
    return _parseServer(argc, argv, host, service, key);
}


//---------------------------- Funciones privadas ----------------------------//

static int _parseClient(int argc, char **argv, char *host, char *service,
                        char *method, char *key) {
    memset(host, 0, HOST_SIZE);
    memset(service, 0, SERVICE_SIZE);
    memset(method, 0, METHOD_SIZE);
    memset(key, 0, KEY_SIZE);

    strncpy(host, argv[HOST_ARG], HOST_SIZE);

    if (atoi(argv[CL_SERVICE_ARG])>0){
        strncpy(service, argv[CL_SERVICE_ARG], SERVICE_SIZE);
    } else {
        fprintf(stderr,"Error: servicio inválido\n");
        return ERROR;
    }
    return _parseMethodAndKey(argc, argv, method, key);
}

static int _parseServer(int argc, char **argv, char *service, char *method,
                        char *key){
    memset(service, 0, SERVICE_SIZE);
    memset(method, 0, METHOD_SIZE);
    memset(key, 0, KEY_SIZE);

    if (atoi(argv[SV_SERVICE_ARG])>0){
        strncpy(service, argv[SV_SERVICE_ARG], SERVICE_SIZE);
    } else {
        fprintf(stderr,"Error: servicio inválido\n");
        return ERROR;
    }
    return _parseMethodAndKey(argc, argv, method, key);
}

static void _extractOption(const char *recv_option, char *option){
    bool eq_sign_found = false;
    int j = 0;
    int length = (int)strlen(recv_option);
    for (int i=0; i<length; i++){
        if (eq_sign_found && recv_option[i] != '"'){
            option[j] = recv_option[i];
            j++;
        } else if (recv_option[i]=='='){
            eq_sign_found = true;
        }
    }
}

static int _parseMethodAndKey(int argc, char **argv, char *method, char *key) {
    char recv_method[METHOD_SIZE];
    char recv_key[KEY_SIZE];
    memset(recv_method, 0, METHOD_SIZE);
    memset(recv_key, 0, KEY_SIZE);

    static struct option long_options[] = {
            {"method",    required_argument, 0,  'm' },
            {"key",   required_argument, 0,  'k' },
            {0,           0,                 0,  0   }
    };
    int opt;
    int long_index = 0;
    while ((opt = getopt_long(argc, argv,"mk",
                              long_options, &long_index)) != -1) {
        switch (opt) {
            case 'm' :
                strncpy(recv_method, argv[optind-1], METHOD_SIZE);
                _extractOption(recv_method, method);
                break;
            case 'k' :
                strncpy(recv_key, argv[optind-1], KEY_SIZE);
                _extractOption(recv_key, key);
                break;
            default:
                fprintf(stderr,"Opción inválida\n");
                return ERROR;
        }
    }
    return SUCCESS;
}

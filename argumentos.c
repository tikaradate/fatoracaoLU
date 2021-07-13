/*
 * Autores:
 *   Jorge Lucas Vicilli Jabczenski
 *     GRR20190372
 *   Vinicius Tikara Venturi Date
 *     GRR20190367  
 *
 */
#include <argp.h>
#include <stdlib.h>
#include <string.h>

#include "argumentos.h"
/* estruturas e funções necessárias para o argp.h */

/* 
   struct básica do argp.h, 
   auxilia na documentação dos argumentos da linha de comando
*/
static struct argp_option options[] = {
    {0, 'p', 0, 0, "Paramêtro que indica se deve ser feito o pivoteamento parcial"},
    {"output", 'o', "OUTPUT", 0, "Escreve em OUTPUT invés de stdout"},
    {0}};

/*
    função necessária da biblioteca argp que analisa os argumentos
    e adequada os campos da struct argumentos
*/
static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    struct argumentos *args = state->input;

    switch (key) {
        case 'p':
            args->pivo = 1;
            break;
        case 'o':
            args->output = arg;
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

/*
    TODO
*/
static struct argp argp = {options, parse_opt, 0, 0};
/* fim parte necessária de argp.h */

struct argumentos linha_de_comando(int argc, char *argv[]) {
    struct argumentos args;

    args.pivo = 0;
    args.output = NULL;

    argp_parse(&argp, argc, argv, 0, 0, &args);

    return args;
}

FILE* arruma_output(char *output) {
    // se houver um caminho em output, tenta abrir
    if (output != NULL) {
        FILE *ret = fopen(output, "w");\
        // testa fopen
        if (!ret) {
            perror("Erro ao abrir output:");
            exit(1);
        }
        return ret;
    }
    // se nao retorna a saida padrao
    return (stdout);
}
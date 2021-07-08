#include "argumentos.h"

#include <argp.h>
#include <stdlib.h>
#include <string.h>

/* estruturas e funções necessárias para o argp.h */

// breve descricao das opcoes
static struct argp_option options[] = {
    {0, 'p', 0, 0, "Paramêtro que indica se deve ser feito o pivoteamento parcial"},
    {"output", 'o', "OUTPUT", 0, "Escreve em OUTPUT invés de stdout"},
    {0}};

// funcao que analisa os argumentos
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

// struct necessaria de argp_parse
static struct argp argp = {options, parse_opt, 0, 0};
/* fim parte argp.h */

struct argumentos linha_de_comando(int argc, char *argv[]) {
    struct argumentos args;

    args.pivo = 0;
    args.output = NULL;

    argp_parse(&argp, argc, argv, 0, 0, &args);

    return args;
}
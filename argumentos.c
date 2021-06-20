#include "argumentos.h"

#include <argp.h>
#include <stdlib.h>
#include <string.h>

/* estruturas e funções necessárias para o argp.h */

// descricao dos argumentos sem opcao
static char args_doc[] = "(para wavcat/wavmix) [FILE.wav ...]";

// breve descricao das opcoes
static struct argp_option options[] = {
    {"input", 'i', "INPUT", 0, "Lê de INPUT invés de stdin"},
    {"output", 'o', "OUTPUT", 0, "Escreve em OUTPUT invés de stdout"},
    {"level", 'l', "LEVEL", 0,
     "Fator de ajuste de alguns efeitos (wavecho, wavvol, wavwide)"},
    {"delay", 't', "DELAY", 0, "Delay, em ms (wavecho)"},
    {0}};

// funcao que analisa os argumentos
static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    struct argumentos *args = state->input;

    switch (key) {
        case 'i':
            args->input = arg;
            break;
        case 'o':
            args->output = arg;
            break;
        case 'l':
            args->level = atof(arg);
            break;
        case 't':
            args->delay = atof(arg);
            break;
        case ARGP_KEY_ARG:
            // como temos o indice o proximo e queremos o atual,
            // decrescemos state->next
            state->next--;
            // o ponteiro de strings "arquivos" recebe
            // o endereco dos argumentos sem opcoes, isto eh,
            // os arquivos usados em wavcat e wavmix
            args->arquivos = &state->argv[state->next];
            // forca a finalizacao da leitura dos argumentos da linha de comando
            state->next = state->argc;
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

// struct necessaria de argp_parse
static struct argp argp = {options, parse_opt, args_doc, 0};
/* fim parte argp.h */

struct argumentos linha_de_comando(int argc, char *argv[]) {
    struct argumentos args;
    char *nome_programa;

    nome_programa = argv[0];

    args.input = NULL;
    args.output = NULL;
    // com base no nome programa, escolhe o valor default para -l
    if (strcmp(nome_programa, "./wavecho") == 0) {
        args.level = LEVEL_ECHO;
    } else if (strcmp(nome_programa, "./wavwide") == 0) {
        args.level = LEVEL_WIDE;
    } else if (strcmp(nome_programa, "./wavvol") == 0) {
        args.level = LEVEL_VOL;
    } else {
        args.level = 0;
    }
    args.delay = DELAY_ECHO;

    argp_parse(&argp, argc, argv, 0, 0, &args);

    // checa se os argumentos estao dentro do intervalo
    // se nao for o caso, usa o maximo ou minimo do intervalo
    if (strcmp(nome_programa, "./wavecho") == 0) {
        if (args.level > MAX_LEVEL_ECHO) args.level = MAX_LEVEL_ECHO;
        if (args.level < MIN_LEVEL_ECHO) args.level = MIN_LEVEL_ECHO;
    } else if (strcmp(nome_programa, "./wavwide") == 0) {
        if (args.level > MAX_LEVEL_WIDE) args.level = MAX_LEVEL_WIDE;
        if (args.level < MIN_LEVEL_WIDE) args.level = MIN_LEVEL_WIDE;
    } else if (strcmp(nome_programa, "./wavvol") == 0) {
        if (args.level > MAX_LEVEL_VOL) args.level = MAX_LEVEL_VOL;
        if (args.level < MIN_LEVEL_VOL) args.level = MIN_LEVEL_VOL;
    }
    if (args.delay < MIN_DELAY_ECHO) args.delay = MIN_DELAY_ECHO;

    return args;
}
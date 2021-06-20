#ifndef __ANALISE_ARGS__
#define __ANALISE_ARGS__
#include <stdio.h>

// valores default de alguns efeitos
#define LEVEL_VOL  1.0
#define LEVEL_ECHO 0.5
#define LEVEL_WIDE 1.0
#define DELAY_ECHO 1000

// minimos e maximos de alguns efeitos
#define MIN_LEVEL_VOL  0
#define MAX_LEVEL_VOL  10.0
#define MIN_LEVEL_ECHO 0
#define MAX_LEVEL_ECHO 1.0
#define MIN_LEVEL_WIDE 0
#define MAX_LEVEL_WIDE 10.0
#define MIN_DELAY_ECHO 0

// struct que guarda a informacao das opcoes dos efeitos
struct argumentos {
    char *input;
    char *output;
    char **arquivos;
    float level;
    float delay;
};

// le os argumentos da linha de comando e os trata
struct argumentos linha_de_comando(int argc, char *argv[]);

#endif
#ifndef __ANALISE_ARGS__
#define __ANALISE_ARGS__
#include <stdio.h>

// struct que guarda a informacao das opcoes dos efeitos
struct argumentos {
    char *output;
    int pivo;
};

// le os argumentos da linha de comando e os trata
struct argumentos linha_de_comando(int argc, char *argv[]);

#endif
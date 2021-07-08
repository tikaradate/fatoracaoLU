#include <math.h>
#include <stdio.h>

#include "utils.h"

/*  Retorna tempo em milisegundos

    Forma de uso:
 
    double tempo;
    tempo = timestamp();
    <trecho de programa do qual se deseja medir tempo>
    tempo = timestamp() - tempo;
*/

double timestamp(void)
{
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return ((double)(tp.tv_sec * 1000.0 + tp.tv_usec / 1000.0));
}

FILE *arruma_output(char *output) {
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
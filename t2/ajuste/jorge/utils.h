/*
 * Autores:
 *   Jorge Lucas Vicilli Jabczenski
 *     GRR20190372
 *   Vinicius Tikara Venturi Date
 *     GRR20190367  
 *
 */
#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdlib.h>
#include <sys/time.h>

#define MAXIT 50

/*  Retorna tempo em milisegundos

    Forma de uso:
 
    double tempo;
    tempo = timestamp();
    <trecho de programa do qual se deseja medir tempo>
    tempo = timestamp() - tempo;
*/
double timestamp(void);
/* 
    descrição: função que aloca e checa se o vetor foi alocado corretamente
    paramêtros: 
        n: quantidade de elementos
    retorno: ponteiro para o vetor recém-alocado.
*/
double *alocaVet(int n);
#endif // __UTILS_H__

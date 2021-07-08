#ifndef __MATRIZ__
#define __MATRIZ__
#include <stdio.h>
/* 
    atributos:
        n: ordem da matriz
        m: ponteiro para um vetor de ponteiros(matriz)
 */
struct matriz{
    int n;
    double **m;
};

/* 
    descrição: 
    paramêtros: 
*/

/* 
    descrição: função auxiliar de alocar matriz 
    paramêtros: 
        n: a ordem da matriz
    retorno: ponteiro para uma struct matriz
*/
struct matriz *alocaMatriz(int n);

/* 
    descrição: função auxiliar para liberar a struct matriz 
    paramêtros: 
        matriz: a matriz a ser liberada
*/
void liberaMatriz(struct matriz *matriz);

/* 
    descrição: lê uma matriz já alocada
    paramêtros: 
        matriz: a matriz aonde amarzena-se os valores lidos
*/
void leMatriz(struct matriz *matriz);

/* 
    descrição: imprime a informação da matriz dada
    paramêtros:
        matriz: a matriz a ser impressa
*/
void imprimeMatriz(struct matriz *matriz, FILE *out);

void copiaMatriz(struct matriz *source, struct matriz *dest);

void trocaLinha(struct matriz *M, int atual, int pivo);

double *pegaColuna(struct matriz *M, int c);

void botaColuna(struct matriz *M, int c, double *col);

#endif
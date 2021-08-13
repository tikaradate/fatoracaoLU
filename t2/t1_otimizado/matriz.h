/*
 * Autores:
 *   Jorge Lucas Vicilli Jabczenski
 *     GRR20190372
 *   Vinicius Tikara Venturi Date
 *     GRR20190367  
 *
 */
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
    double *m;
};

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
/* 
    descrição: copia os valores da matriz source para a matriz dest
    paramêtros:
        source: a matriz a ser copiada
        dest: a matriz que recebe a cópia
*/
void copiaMatriz(struct matriz *source, struct matriz *dest);
/* 
    descrição: função que troca as linha atual da matriz com a linha do pivo da matriz
    paramêtros: 
        matriz: a matriz que terá as linhas trocadas
        atual : a linha da matriz atual
        pivo  : a linha com o maior elemento que trocará de lugar com a linha atual
*/
void trocaLinha(struct matriz *matriz, int atual, int pivo);
/* 
    descrição: função que retorna a coluna da matriz indicada por c 
    paramêtros: 
        matriz: a matriz que terá a coluna copiada
        c     : indica qual coluna vai ser copiada
    retorno: um ponteiro para a coluna
*/
double *pegaColuna(struct matriz *matriz, int c);
/* 
    descrição: função que insere a coluna indicada por c na matriz
    paramêtros: 
        matriz: a matriz que receberá a coluna
        c     : indica qual coluna da matriz receberá os valores
        col   : ponteiro que contém a coluna a ser copiada
*/
void botaColuna(struct matriz *matriz, int c, double *col);
/* 
    descrição: função que checa se dada matriz na sua forma triangular é inversível
    paramêtros: 
        matriz: a matriz que será analisada
    retorno: 1 se inversível, 0 caso contrário
*/
int checaInversibilidade(struct matriz *matriz);

#endif
/*
 * Autores:
 *   Jorge Lucas Vicilli Jabczenski
 *     GRR20190372
 *   Vinicius Tikara Venturi Date
 *     GRR20190367  
 *
 */

#ifndef __GAUSS__
#define __GAUSS__
/* 
    descrição: realiza a triangularização de uma dada matriz(A), a separando em upper(U) e lower(L), levando em conta o pivoteamento
               opcional em todas as matrizes que podem ser afetadas
    paramêtros: 
        A : a matriz original
        L : a matriz lower
        U : a matriz upper
        Id: a matriz identidade
        pivoteia: paramêtro que indica se é necessário o pivoteamento
        tempo: variável que armazena o tempo das operações
    retorno:
        -1 se teve algum NaN ou inf e 0 se tudo ok
*/
int triangularizacao(struct matriz *L, struct matriz *U, struct matriz *funcoes);

int triangularizacao_original(struct matriz *L, struct matriz *U, struct matriz *funcoes);

/* 
    descrição: encontra o maior elemento de tal coluna
    paramêtros: 
        matriz: a matriz que vai ser percorrida
        c     : a coluna que irá ser fixa
    retorno: a linha com o maior elemento da coluna indicada
*/
int encontraMax(struct matriz *matriz, int c);
/* 
    descrição: faz a retrossubstituição de uma matriz triangular superior
    paramêtros: 
        matriz: a matriz que será feita a retrossubstituição
        b     : o vetor que age como vetor resposta
        tempo : variável que armazena o tempo das operações
        x     : ponteiro para o vetor resposta da retrossubstituição
    retorno: 0 se tudo certo, -1 se alguma conta gerou um número dúbio
*/
int retrossub(struct matriz *matriz, double* b, double **x);
/* 
    descrição: faz a retrossubstituição de uma matriz triangular inferior
    paramêtros:
        matriz: a matriz que será feita a retrossubstituição
        b     : o vetor que age como vetor resposta
        tempo: variável que armazena o tempo das operações
        x     : ponteiro para o vetor resposta da retrossubstituição
    retorno: 0 se tudo certo, -1 se alguma conta gerou um número dúbio
*/
int retrossubLower(struct matriz *matriz, double* b, double **x);
/* 
    descrição: função que calcula o resíduo de dado vetor resultante
    paramêtros: 
        matriz: a matriz que será usada para calcular o resíduo
        x     : o vetor resultante que será testado
        colId : a coluna da matriz identidade que é a solução analítica
    retorno: ponteiro que contém os valores residuais 
*/
double *residuo(struct matriz *matriz, double *x, double *colId);
/* 
    descrição: calcula a normaL2 de um resíduo
    paramêtros:
        n   : a ordem da matriz que gerou o resíduo
        res : o ponteiro que contém os valores do resíduo
    retorno: a norma L2 desse resíduo
*/
double normaL2Residuo(int n, double *res);
#endif
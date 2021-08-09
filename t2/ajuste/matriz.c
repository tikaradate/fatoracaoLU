/*
 * Autores:
 *   Jorge Lucas Vicilli Jabczenski
 *     GRR20190372
 *   Vinicius Tikara Venturi Date
 *     GRR20190367  
 *
 */
#include <stdio.h>
#include <stdlib.h>

#include "matriz.h"

struct matriz *alocaMatriz(int m, int n)
{
    struct matriz *matriz;
    matriz = malloc(sizeof(struct matriz));
    if(!matriz){
        fprintf(stderr, "Falha ao alocar estrutura da matriz, abortando...\n");
        exit(1);
    }

    matriz->m = m;
    matriz->n = n;
    matriz->mat = malloc(sizeof(double *)*n*m);
    if(!matriz->mat){
        fprintf(stderr, "Falha ao alocar vetor de ponteiros de %d posições, abortando...\n", n);
        exit(1);
    }

    return matriz;
}

void liberaMatriz(struct matriz *matriz)
{
    free(matriz->mat);
    free(matriz);
}

void leMatriz(struct matriz *matriz)
{   
    int m = matriz->m;
    int n = matriz->n;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%lf", &matriz->mat[i*n + j]);
        }
    }
}

void imprimeMatriz(struct matriz *matriz, FILE *out)
{
    int m = matriz->m;
    int n = matriz->n;

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fprintf(out ,"%.8e ", matriz->mat[i*n + j]);
        }
        fputc('\n', out);
    }
}

void copiaMatriz(struct matriz *source, struct matriz *dest)
{
    int m = source->m;
    int n = source->n;

    dest->m = m;
    dest->n = n;

	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			dest->mat[i*n + j] = source->mat[i*n + j];
}

void trocaLinha(struct matriz *matriz, int atual, int pivo)
{
	double aux;
    int m = matriz->m;
    int n = matriz->n;
	for (int i = 0; i < m; i++)
	{
		aux = matriz->mat[atual*n + i];
		matriz->mat[atual*n + i] = matriz->mat[pivo*n + i];
		matriz->mat[pivo*n + i] = aux;
    }
}

double* pegaLinha(struct matriz *matriz, int l){

    int n = matriz->n;
    double* lin = calloc(n, sizeof(double));
    if(!lin){
        fprintf(stderr, "Falha ao alocar vetor de %d posições, abortando...\n", n);
        exit(1);
    }

    for(int i = 0; i < n; i++){
        lin[i] = matriz->mat[l*n + i];
    }
    return lin;
}

double* pegaColuna(struct matriz *matriz, int c){

    int m = matriz->m;
    int n = matriz->n;
    double* col = calloc(n, sizeof(double));
    if(!col){
        fprintf(stderr, "Falha ao alocar vetor de %d posições, abortando...\n", n);
        exit(1);
    }

    for(int i = 0; i < m; i++){
        col[i] = matriz->mat[i*n + c];
    }
    return col;
}

void botaColuna(struct matriz *matriz, int c, double *col){

    int m = matriz->m;
    int n = matriz->n;

    for(int i = 0; i < m; i++){
        matriz->mat[i*n + c] = col[i];
    }
}

int checaInversibilidade(struct matriz *matriz){
    double mult = 1;
    int m = matriz->m;
    int n = matriz->n;
    for(int i = 0; i < m; i++){
        mult *= matriz->mat[i*n + i];
    }
    return (mult != 0);
}
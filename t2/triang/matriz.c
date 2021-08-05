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

struct matriz *alocaMatriz(int n)
{
    struct matriz *matriz;
    matriz = malloc(sizeof(struct matriz));
    if(!matriz){
        fprintf(stderr, "Falha ao alocar estrutura da matriz, abortando...\n");
        exit(1);
    }

    matriz->n = n;
    matriz->m = malloc(sizeof(double *)*n*n);
    if(!matriz->m){
        fprintf(stderr, "Falha ao alocar vetor de ponteiros de %d posições, abortando...\n", n);
        exit(1);
    }

    return matriz;
}

void liberaMatriz(struct matriz *matriz)
{
    free(matriz->m);
    free(matriz);
}

void leMatriz(struct matriz *matriz)
{
    int n = matriz->n;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%lf", &matriz->m[i*n + j]);
        }
    }
}

void imprimeMatriz(struct matriz *matriz, FILE *out)
{
    int n = matriz->n;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fprintf(out ,"% .6e ", matriz->m[i*n + j]);
        }
        fputc('\n', out);
    }
}

void copiaMatriz(struct matriz *source, struct matriz *dest)
{
    int n = source->n;
    dest->n = n;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			dest->m[i*n + j] = source->m[i*n + j];
}

void trocaLinha(struct matriz *matriz, int atual, int pivo)
{
	double aux;
    int n = matriz->n;
	for (int i = 0; i < n; i++)
	{
		aux = matriz->m[atual*n + i];
		matriz->m[atual*n + i] = matriz->m[pivo*n + i];
		matriz->m[pivo*n + i] = aux;
    }
}

double* pegaColuna(struct matriz *matriz, int c){
    int n = matriz->n;
    double* col = calloc(n, sizeof(double));
    if(!col){
        fprintf(stderr, "Falha ao alocar vetor de %d posições, abortando...\n", n);
        exit(1);
    }

    for(int i = 0; i < n; i++){
        col[i] = matriz->m[i*n + c];
    }
    return col;
}

void botaColuna(struct matriz *matriz, int c, double *col){
    int n = matriz->n;

    for(int i = 0; i < n; i++){
        matriz->m[i*n + c] = col[i];
    }
}

int checaInversibilidade(struct matriz *matriz){
    double mult = 1;
    int n = matriz->n;
    for(int i = 0; i < n; i++){
        mult *= matriz->m[i*n + i];
    }
    return (mult != 0);
}
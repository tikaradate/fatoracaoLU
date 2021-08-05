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
    matriz->m = malloc(sizeof(double *) * n);
    if(!matriz->m){
        fprintf(stderr, "Falha ao alocar vetor de ponteiros de %d posições, abortando...\n", n);
        exit(1);
    }
    for (int i = 0; i < n; i++){
        matriz->m[i] = calloc(n, sizeof(double));
        if(!matriz->m[i]){
            fprintf(stderr, "Falha ao alocar vetor de %d posições, abortando...\n", n);
            exit(1);
        }
    }

    return matriz;
}

void liberaMatriz(struct matriz *matriz)
{
    for (int i = 0; i < matriz->n; i++)
        free(matriz->m[i]);

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
            scanf("%lf", &matriz->m[i][j]);
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
            fprintf(out ,"% .0f ", matriz->m[i][j]);
        }
        fputc('\n', out);
    }
    fprintf(out ,"-----\n");
}

void copiaMatriz(struct matriz *source, struct matriz *dest)
{
    int n = source->n;
    dest->n = n;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			dest->m[i][j] = source->m[i][j];
}

void trocaLinha(struct matriz *matriz, int atual, int pivo)
{
	double aux;
	for (int i = 0; i < matriz->n; i++)
	{
		aux = matriz->m[atual][i];
		matriz->m[atual][i] = matriz->m[pivo][i];
		matriz->m[pivo][i] = aux;
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
        col[i] = matriz->m[i][c];
    }
    return col;
}

void botaColuna(struct matriz *matriz, int c, double *col){
    int n = matriz->n;

    for(int i = 0; i < n; i++){
        matriz->m[i][c] = col[i];
    }
}

int checaInversibilidade(struct matriz *matriz){
    double mult = 1;
    for(int i = 0; i < matriz->n; i++){
        mult *= matriz->m[i][i];
    }
    return (mult != 0);
}
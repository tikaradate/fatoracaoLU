#include <stdio.h>
#include <stdlib.h>

#include "matriz.h"

struct matriz *alocaMatriz(int n)
{
    struct matriz *matriz;
    matriz = malloc(sizeof(struct matriz));

    matriz->n = n;
    matriz->m = malloc(sizeof(double *) * n);
    for (int i = 0; i < n; i++)
        matriz->m[i] = calloc(n, sizeof(double));

    return matriz;
}

void liberaMatriz(struct matriz *matriz)
{

    for (int i = 0; i < matriz->n; i++)
        free(matriz->m[i]);

    free(matriz->m);
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
            fprintf(out ,"% .6e ", matriz->m[i][j]);
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
			dest->m[i][j] = source->m[i][j];
}

void trocaLinha(struct matriz *M, int atual, int pivo)
{
	double aux;
	for (int i = 0; i < M->n; i++)
	{
		aux = M->m[atual][i];
		M->m[atual][i] = M->m[pivo][i];
		M->m[pivo][i] = aux;
    }
}

double* pegaColuna(struct matriz *M, int c){
    int n = M->n;
    double* col = calloc(n, sizeof(double));

    for(int i = 0; i < n; i++){
        col[i] = M->m[i][c];
    }
    return col;
}

void botaColuna(struct matriz *M, int c, double *col){
    int n = M->n;

    for(int i = 0; i < n; i++){
        M->m[i][c] = col[i];
    }
}

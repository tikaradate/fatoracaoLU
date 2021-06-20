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
        matriz->m[i] = malloc(sizeof(double) * n);

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

void imprimeMatriz(struct matriz *matriz)
{
    int n = matriz->n;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("% .6e ", matriz->m[i][j]);
        }
        putchar('\n');
    }
}
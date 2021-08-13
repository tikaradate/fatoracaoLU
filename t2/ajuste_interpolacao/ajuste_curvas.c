#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ajuste_curvas.h"
#include "matriz.h"
#include "gauss.h"

struct matriz *montaAjuste(struct matriz *x)
{
    struct matriz *kurwa;
    int n = x->n;
    double *somas = calloc(n + n, sizeof(double));
    double *pot = calloc(n * (n + n), sizeof(double));

    for (int i = 0; i < n; i++)
    {
        pot[i] = 1;
        somas[0] += 1;
    }

    for (int i = 1; i < n + n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            pot[i * n + j] = pot[(i - 1) * n + j] * x->mat[j];
            somas[i] += pot[i * n + j];
        }
    }

    // preenche a matriz com os somatórios realizados acima
    kurwa = alocaMatriz(n, n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            kurwa->mat[i * n + j] = somas[i + j];
        }
    }

    free(somas);

    return kurwa;
}

int ajusta(struct matriz *U, struct matriz *L, struct matriz *funcoes, struct matriz *pontos, int i, FILE *out)
{
    int n, flag;
    n = U->n;
    flag = 0;

    double *x = NULL;
    double *y = NULL;
    double *b = calloc(n, sizeof(double));

    for (int j = 0; j < n; j++)
    {
        for (int k = 0; k < n; k++)
        {
            b[j] += funcoes->mat[i * n + k] * pow(pontos->mat[k], j);
        }
    }

    // acha y (Ly = b)
    flag = retrossubLower(L, b, &y);
    if (flag != 0)
    {
        free(b);
        return flag;
    }
    // acha x (Ux = y)
    flag = retrossub(U, y, &x);
    if (flag != 0)
    {
        free(b);
        free(y);
        return flag;
    }
    for (int j = 0; j < n; j++)
    {
        fprintf(out, "%lf ", x[j]);
    }
    fprintf(out, "\n");
    free(b);
    free(x);
    free(y);
    return 0;
}
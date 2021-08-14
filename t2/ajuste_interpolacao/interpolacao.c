#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "interpolacao.h"
#include "matriz.h"
#include "gauss.h"

struct matriz *montaInterpolacao(struct matriz *x)
{
    struct matriz *mat;
    int n = x->n;
    mat = alocaMatriz(n, n);

    // cálculo das potências da matriz da interpolação
    for(int i = 0; i < n; i++)
         mat->mat[i*n] = 1;

    for(int i = 0; i < n; i++)
        for(int j = 1; j < n; j++)
            mat->mat[i*n + j] = mat->mat[i*n + (j-1)]*x->mat[i];

    return mat;
}

int interpola(struct matriz *U, struct matriz *L, struct matriz *funcoes, int i, FILE *out)
{
    int flag;
    flag = 0;

    double *x = NULL,
           *y = NULL,
           *b = NULL;
    // pega a linha das funções a ser usada como b
    b = pegaLinha(funcoes, i);

    // acha y (Ly = b)
    flag = retrossubLower(L, b, &y);
    if (!y)
    {
        free(b);
        return flag;
    }
    // acha x (Ux = y)
    flag = retrossub(U, y, &x);
    if (!x)
    {
        free(b);
        free(y);
        return flag;
    }
    // imprime o resultado
    for (int j = 0; j < U->n; j++)
        fprintf(out, "%lf ", x[j]);

    fprintf(out,"\n");

    free(b);
    free(x);
    free(y);
    return 0;
}

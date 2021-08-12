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

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            mat->mat[i * n + j] = pow(x->mat[i], j);
        }
    }
    // for(int i = 0; i < n; i++){
    //      mat->mat[i*n] = 1;
    // }

    // for(int i = 0; i < n; i++){
    //     for(int j = 1; j < n; j++){
    //         mat->mat[i*n + j] = mat->mat[i*n + (j-1)]*x->mat[i];
    //     }
    // }

    return mat;
}

int interpola(struct matriz *pontos, struct matriz *funcoes, int i)
{
    struct matriz *L, *U;
    int n, flag;

    n = pontos->n;
    flag = 0;

    U = montaInterpolacao(pontos);
    L = alocaMatriz(n, n);

    if (triangularizacao(L, U) != 0)
    {
        printf("porra deu diferente de 0?\n");
    }
    else
    {
        double *x = NULL,
               *y = NULL,
               *b = NULL;
        // pega a coluna da matriz identidade a ser usada como b
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
        for (int j = 0; j < n; j++)
        {
            printf("%lf ", x[j]);
        }
        printf("\n");
        free(b);
        free(x);
        free(y);
    }
    liberaMatriz(U);
    liberaMatriz(L);
    return 0;
}
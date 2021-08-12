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

    // calcula as potências a partir da ideia de acessar o anterior e multiplicar pela base
    // e faz a soma na hora

    for (int i = 0; i < n; i++)
    {
        pot[i] = 1;
    }

    for (int i = 0; i < n + n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i != 0)
            {
                pot[i * n + j] = pot[(i - 1) * n + j] * x->mat[j];
            }
            somas[i] += pot[i * n + j];
            // somas[i] += pow(x->mat[j], i);
        }
    }

    // for (int i = 0; i < n + n; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         if(i != 0){
    //             pot[i*n + j] = pot[(i-1)*n + j]*x->mat[j];
    //             somas[i] += pot[i*n + j];
    //         }
    //         else{
    //             pot[i*n + j] = 1;
    //             somas[i] += 1;
    //         }
    //         // somas[i] += pow(x->mat[j], i);
    //     }
    // }

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

int ajusta(struct matriz *pontos, struct matriz *funcoes, struct matriz *somatorios, int i)
{
    struct matriz *U, *L;
    int n, flag;

    flag = 0;
    n = somatorios->n;

    U = alocaMatriz(n, n);
    L = alocaMatriz(n, n);
    copiaMatriz(somatorios, U);

    if (triangularizacao(L, U) != 0)
    {
        printf("porra deu diferente de 0?\n");
    }
    else
    {
        double *x = NULL;
        double *y = NULL;
        double *b = calloc(n + 1, sizeof(double));

        for (int j = 0; j <= n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                b[j] += funcoes->mat[i * n + k] * pow(pontos->mat[k], j);
            }
        }

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
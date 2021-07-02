#include <stdio.h>
#include "matriz.h"
#include "argumentos.h"

void triangularizacao(struct matriz *L, struct matriz *U, int pivoteia);

int encontraMax(struct matriz *M, int l);

void trocaLinha(struct matriz *M, int atual, int pivo);


int main(int argc, char *argv[])
{
    int n;
    struct matriz *L, *U, *I;
    struct argumentos args;

    args = linha_de_comando(argc, argv);
    while (scanf("%d", &n) != EOF)
    {
        U = alocaMatriz(n);
        L = alocaMatriz(n);
        // o que sobra da eliminação já é a matriz U
        leMatriz(U);
        imprimeMatriz(U);
        printf("\n");

        triangularizacao(L, U, args.pivo);

        imprimeMatriz(L);
        printf("\n");
        imprimeMatriz(U);
        printf("\n");

        liberaMatriz(L);
        liberaMatriz(U);
    }
    return 0;
}

void triangularizacao(struct matriz *L, struct matriz *U, int pivoteia)
{
    int n = U->n;

    for (int i = 0; i < n; ++i)
    {
        if (pivoteia)
        {   
            int i_pivo = encontraMax(U, i);
            if (i != i_pivo)
            {
                trocaLinha(U, i, i_pivo);
            }
        }

        for (int j = i + 1; j < n; j++)
        {
            double m = U->m[j][i] / U->m[i][i];

            U->m[j][i] = 0.0;
            for (int k = i + 1; k < n; k++)
                U->m[j][k] -= U->m[i][k] * m;

            L->m[j][i] = m;
        }
        L->m[i][i] = 1;
    }
}

int encontraMax(struct matriz *M, int l)
{
	float max = 0;
	int max_l = l;
	for (int i = 0; i < l; i++)
	{
		if (max < M->m[l][i])
		{
			max = M->m[l][i];
			max_l = i;
		}
	}
	return max_l;
}

void trocaLinha(struct matriz *M, int atual, int pivo)
{
	int aux;
	for (int i = 0; i < M->n; i++)
	{
		aux = M->m[atual][i];
		M->m[atual][i] = M->m[pivo][i];
		M->m[pivo][i] = aux;
    }
}

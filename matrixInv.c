#include <stdio.h>

#include "utils.h"
#include "matriz.h"
#include "argumentos.h"

void triangularizacao(struct matriz *L, struct matriz *U, int pivoteia, double *tempo);

int encontraMax(struct matriz *M, int l);

void trocaLinha(struct matriz *M, int atual, int pivo);


int main(int argc, char *argv[])
{
    int n;
    double tempo;
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

        triangularizacao(L, U, args.pivo, &tempo);
        printf("Tempo Triangularização: %.50lf ms\n", tempo);
        imprimeMatriz(L);
        printf("\n");
        imprimeMatriz(U);
        printf("\n");

        liberaMatriz(L);
        liberaMatriz(U);
    }
    return 0;
}

void triangularizacao(struct matriz *L, struct matriz *U, int pivoteia, double *tempo)
{
    int n = U->n;
    *tempo = timestamp();
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
    *tempo = timestamp() - *tempo;
}

int encontraMax(struct matriz *M, int l)
{
	float max = 0;
	int max_l = l;
	for (int i = l; i < M->n; i++)
	{
		if (max < M->m[i][l])
		{
			max = M->m[i][l];
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

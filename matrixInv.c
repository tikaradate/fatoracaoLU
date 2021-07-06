#include <stdio.h>
#include <math.h>

#include "utils.h"
#include "matriz.h"
#include "argumentos.h"

void triangularizacao(struct matriz *A, struct matriz *L, struct matriz *U, struct matriz *I, int pivoteia, double *tempo);

int encontraMax(struct matriz *M, int l);

void trocaLinha(struct matriz *M, int atual, int pivo);

double* pegaColuna(struct matriz *M, int c);

void botaColuna(struct matriz *M, int c, double *col);

double* retrossub(struct matriz *M, double* b);

double* retrossubLower(struct matriz *M, double* b);

double* residuo(struct matriz *M, double *x, double *colId);

double normaL2Residuo(int n, double *res);

void copiaMatriz(struct matriz *source, struct matriz *dest);

int main(int argc, char *argv[])
{
    int n;
    double tempo;
    double *x, *y, *b;
    struct matriz *A, *L, *U, *Id, *Inv;
    struct argumentos args;

    args = linha_de_comando(argc, argv);
    while (scanf("%d", &n) != EOF)
    {
        A   = alocaMatriz(n);
        U   = alocaMatriz(n);
        L   = alocaMatriz(n);
        Inv = alocaMatriz(n);
        Id  = alocaMatriz(n);
        for(int i = 0; i < n; i++){
            Id->m[i][i] = 1; 
        }

        leMatriz(A);
        imprimeMatriz(A);
        printf("\n");

        // precisamos preservar a matriz original para o cálculo das normas L2 dos resíduos
        copiaMatriz(A, U);

        triangularizacao(A, L, U, Id, args.pivo, &tempo);
        printf("Tempo Triangularização: %.50lf ms\n", tempo);
        imprimeMatriz(L);
        printf("\n");
        imprimeMatriz(U);
        printf("\n");
        imprimeMatriz(Id);
        printf("\n");

        // Ly = b
        // Ux = y
        for(int i = 0; i < n; i++){
            // pega a coluna a ser usada como b
            b = pegaColuna(Id, i);
            // acha y (Ly = b)
            y = retrossubLower(L, b);
            // acha x (Ux = y) e bota na matriz Inv
            botaColuna(Inv, i, retrossub(U, y));
        }

        imprimeMatriz(Inv);
        printf("\n");

        for(int i = 0; i < n; i++){
            double *res;
            double *normas = malloc(sizeof(double)*n);
            res = residuo(A, pegaColuna(Inv, i), pegaColuna(Id, i));
            normas[i] = normaL2Residuo(n, res);
            printf("%.16lf ", normas[i]);
        }

        liberaMatriz(L);
        liberaMatriz(U);
        liberaMatriz(Inv);
        liberaMatriz(Id);
    }
    return 0;
}

void triangularizacao(struct matriz *A, struct matriz *L, struct matriz *U, struct matriz *Id, int pivoteia, double *tempo)
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
                trocaLinha(A, i, i_pivo); // efetua a mesma troca de linhas na matriz original
                trocaLinha(Id, i, i_pivo); // efetua a mesma troca de linhas na matriz identidade
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

double* retrossub(struct matriz *M, double* b){
    int n = M->n;
    double *x = calloc(n, sizeof(double));

    for (int i = n - 1; i >= 0; i--)
	{
		x[i] = b[i];
		for (int j = i + 1; j < n; j++)
		{
			x[i] -= M->m[i][j] * x[j];
		}
		x[i] /= M->m[i][i];
    }

    return x;
}

double* retrossubLower(struct matriz *M, double* b){
    int n = M->n;
    double *x = calloc(n, sizeof(double));

    for (int i = 0; i < n; i++)
	{
		x[i] = b[i];
		for (int j = i - 1; j >= 0; j--)
		{
			x[i] -= M->m[i][j] * x[j];
		}
		x[i] /= M->m[i][i];
    }

    return x;
}

double* residuo(struct matriz *M, double *x, double *colId)
{
    int n = M->n;
	double *r;
	r = calloc(n, sizeof(double));

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			r[i] += (M->m[i][j] * x[j]);
		}
		// r tem Ax_n após o for de cima
		// subtraímos de b para então termos o resíduo

		r[i] = colId[i] - r[i];
	}
	return r;
}

double normaL2Residuo(int n, double *res)
{
	double norma = 0;
	for (int i = 0; i < n; i++)
	{
		norma += (res[i] * res[i]);
	}
	return fabs(sqrt(norma));
}

void copiaMatriz(struct matriz *source, struct matriz *dest)
{
    int n = source->n;
    dest->n = n;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			dest->m[i][j] = source->m[i][j];
}
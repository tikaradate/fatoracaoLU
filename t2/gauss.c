/*
 * Autores:
 *   Jorge Lucas Vicilli Jabczenski
 *     GRR20190372
 *   Vinicius Tikara Venturi Date
 *     GRR20190367  
 *
 */
#include <math.h>
#include "matriz.h"
#include "gauss.h"
#include "utils.h"

int triangularizacao(struct matriz *A, struct matriz *L, struct matriz *U, struct matriz *Id, int pivoteia, double *tempo)
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
				// efetua as trocas de linhas nas matrizes necessárias:
				// U, A ,L e Id
				trocaLinha(U,  i, i_pivo);
				trocaLinha(A,  i, i_pivo);
				trocaLinha(L,  i, i_pivo);
				trocaLinha(Id, i, i_pivo);
			}
		}

		for (int j = i + 1; j < n; j++)
		{
			double m = U->m[j][i] / U->m[i][i];

			// if(isnan(m) || isinf(m))
			// 	return -1;

			U->m[j][i] = 0.0;
			for (int k = i + 1; k < n; k++)
				U->m[j][k] -= U->m[i][k] * m;

			L->m[j][i] = m;
		}
		L->m[i][i] = 1;
	}
	*tempo = timestamp() - *tempo;
	return 0;
}

int encontraMax(struct matriz *M, int c)
{
	float max = 0;
	// no começo linha e coluna são iguais
	// por isso temos essa inicialização
	int max_l = c;
	for (int i = c; i < M->n; i++)
	{
		if (max < fabs(M->m[i][c]) && M->m[i][c] != 0 )
		{
			max = M->m[i][c];
			max_l = i;
		}
	}
	return max_l;
}

int retrossub(struct matriz *M, double* b, double *tempo, double **x){
	int n = M->n;
	double *aux = alocaVet(n);

	*tempo = timestamp();
	for (int i = n - 1; i >= 0; i--)
	{
		aux[i] = b[i];
		for (int j = i + 1; j < n; j++)
		{
			aux[i] -= M->m[i][j] * aux[j];
		}
		aux[i] /= M->m[i][i];
		if(isnan(aux[i]) || isinf(aux[i]))
			return -1;
	}
	*tempo = timestamp() - *tempo;
	*x = aux;
	return 0;
}

int retrossubLower(struct matriz *M, double* b, double *tempo, double **x){
	int n = M->n;
	double *aux = alocaVet(n);

	*tempo = timestamp();
	for (int i = 0; i < n; i++)
	{
		aux[i] = b[i];
		for (int j = i - 1; j >= 0; j--)
		{
			aux[i] -= M->m[i][j] * aux[j];
		}
		aux[i] /= M->m[i][i];
		if(isnan(aux[i]) || isinf(aux[i]))
			return -1;
	}

	*tempo = timestamp() - *tempo;
	*x = aux;
	return 0;
}

double* residuo(struct matriz *M, double *x, double *colId)
{
	int n = M->n;
	double *r = alocaVet(n);

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			r[i] += (M->m[i][j] * x[j]);
		}
		// r tem o resultado da multiplicação após o laço acima
		// subtraímos da coluna da matriz Identidade
		// para então termos o resíduo
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
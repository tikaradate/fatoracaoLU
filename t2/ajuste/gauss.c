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

int triangularizacao(struct matriz *L, struct matriz *U)
{
	int m = U->m;
	int n = U->n;
	for (int i = 0; i < m; ++i)
	{

		int i_pivo = encontraMax(U, i);
		if (i != i_pivo)
		{  
			// efetua as trocas de linhas nas matrizes necessárias:
			// U e L 
			trocaLinha(U,  i, i_pivo);
			trocaLinha(L,  i, i_pivo);
		}

		for (int j = i + 1; j < n; j++)
		{
			double m = U->mat[j*n + i] / U->mat[i*n + i];

			if(isnan(m) || isinf(m))
				return -1;

			U->mat[j*n + i] = 0.0;
			for (int k = i + 1; k < n; k++)
				U->mat[j*n + k] -= U->mat[i*n + k] * m;

			L->mat[j*n + i] = m;
		}
		L->mat[i*n + i] = 1;
	}
	return 0;
}

int encontraMax(struct matriz *M, int c)
{
	float max = 0;
	int n =  M->n;
	// no começo linha e coluna são iguais
	// por isso temos essa inicialização
	int max_l = c;
	for (int i = c; i < n; i++)
	{
		if (max < fabs(M->mat[i*n + c]) && M->mat[i*n + c] != 0 )
		{
			max = M->mat[i*n + c];
			max_l = i;
		}
	}
	return max_l;
}

int retrossub(struct matriz *M, double* b, double **x){
	int n = M->n;
	double *aux = alocaVet(n);

	for (int i = n - 1; i >= 0; i--)
	{
		aux[i] = b[i];
		for (int j = i + 1; j < n; j++)
		{
			aux[i] -= M->mat[i*n + j] * aux[j];
		}
		aux[i] /= M->mat[i*n + i];
		if(isnan(aux[i]) || isinf(aux[i]))
			return -1;
	}
	*x = aux;
	return 0;
}

int retrossubLower(struct matriz *M, double* b, double **x){
	int n = M->n;
	double *aux = alocaVet(n);

	for (int i = 0; i < n; i++)
	{
		aux[i] = b[i];
		for (int j = i - 1; j >= 0; j--)
		{
			aux[i] -= M->mat[i*n + j] * aux[j];
		}
		aux[i] /= M->mat[i*n + i];
		// if(isnan(aux[i]) || isinf(aux[i]))
		// 	return -1;
	}

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
			r[i] += (M->mat[i*n + j] * x[j]);
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
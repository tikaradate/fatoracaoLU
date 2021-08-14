/*
 * Autores:
 *   Jorge Lucas Vicilli Jabczenski
 *     GRR20190372
 *   Vinicius Tikara Venturi Date
 *     GRR20190367  
 *
 */
#include <math.h>
#include <likwid.h>
#include "matriz.h"
#include "gauss.h"
#include "utils.h"


extern int padding ;

int triangularizacao_original(struct matriz *L, struct matriz *U, struct matriz *funcoes)
{
	int n = U->n - padding;

	for (int i = 0; i < n; i++)
	{
		int i_pivo = encontraMax(U, i);
		if (i != i_pivo)
		{  
			// efetua as trocas de linhas nas matrizes necessárias:
			// U, L
			trocaLinha(U,  i, i_pivo);
			trocaLinha(L,  i, i_pivo);
			trocaColuna(funcoes, i, i_pivo);
		}

		for (int j = i + 1; j < n ; j++)
		{
			double m1 = U->mat[j * n + i] / U->mat[i * n + i];
			if(isnan(m1) || isinf(m1))
			 	return -1;
				 
			U->mat[j * n + i] = 0.0;
			for (int k = i + 1; k < n; k++)
			{
				U->mat[j * n + k] -= U->mat[i * n + k] * m1;
			}
			L->mat[j * n + i] = m1;
	
		}
		L->mat[i * n + i] = 1;
	}
	return 0;
}

int triangularizacao(struct matriz *L, struct matriz *U, struct matriz *funcoes)
{
	int n = U->n - padding;
	int j;
	int fator = 2;

	for (int i = 0; i < n ; i++)
	{
		// int i_pivo = encontraMax(U, i);
		// if (i != i_pivo)
		// {  
		// 	// efetua as trocas de linhas nas matrizes necessárias:
		// 	// U, L
		// 	trocaLinha(U,  i, i_pivo);
		// 	trocaLinha(L,  i, i_pivo);
		// 	trocaColuna(funcoes, i, i_pivo);
		// }
		for (j = i + 1; (j+fator-1) < n - n % fator; j += fator)
		{
			double m1 = U->mat[j * n + i] / U->mat[i * n + i];
			double m2 = U->mat[(j + 1) * n + i] / U->mat[i * n + i];

			U->mat[j * n + i] = 0.0;
			U->mat[(j + 1) * n + i] = 0.0;

			for (int k = i + 1; k < n; k++)
			{
				U->mat[j * n + k] 		-= U->mat[i * n + k] * m1;
				U->mat[(j + 1) * n + k] -= U->mat[i * n + k] * m2;

			}
			L->mat[j * n + i] 		= m1;
			L->mat[(j + 1) * n + i] = m2;
	
		}
		for (j = j; j < n ; j ++)
		{
			double m1 = U->mat[j * n + i] / U->mat[i * n + i];

			U->mat[j * n + i] = 0.0;
			for (int k = i + 1; k < n; k++)
			{
				U->mat[j * n + k] -= U->mat[i * n + k] * m1;
			}
			L->mat[j * n + i] = m1;
		}
		L->mat[i * n + i] = 1;
	}
	return 0;
}

int encontraMax(struct matriz *M, int c)
{
	float max = 0;
	int n = M->n - padding;
	// no começo linha e coluna são iguais
	// por isso temos essa inicialização
	int max_l = c;
	for (int i = c; i < n; i++)
	{
		if (max < fabs(M->mat[i * n + c]) && M->mat[i * n + c] != 0)
		{
			max = M->mat[i * n + c];
			max_l = i;
		}
	}
	return max_l;
}

int retrossub(struct matriz *M, double *b, double **x)
{
	int n = M->n - padding;
	double *aux = alocaVet(n);

	for (int i = n - 1; i >= 0; i--)
	{
		aux[i] = b[i];
		for (int j = i + 1; j < n; j++)
		{
			// duvidosa
			aux[i] -= M->mat[i * n + j] * aux[j];
		}
		aux[i] /= M->mat[i * n + i];
		// if(isnan(aux[i]) || isinf(aux[i]))
		// 	return -1;
	}
	*x = aux;
	return 0;
}

int retrossubLower(struct matriz *M, double *b, double **x)
{
	int n = M->n - padding;
	double *aux = alocaVet(n);

	for (int i = 0; i < n; i++)
	{
		aux[i] = b[i];
		for (int j = i - 1; j >= 0; j--)
		{
			// duvidosa
			aux[i] -= M->mat[i * n + j] * aux[j];
		}
		aux[i] /= M->mat[i * n + i];
		// if(isnan(aux[i]) || isinf(aux[i]))
		// 	return -1;
	}

	*x = aux;
	return 0;
}

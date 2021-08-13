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
// if(isnan(m1 || isinf(m1))
// 	return -1;

int triangularizacao_original(struct matriz *L, struct matriz *U)
{
	int n = U->n;
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n ; j++)
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


int triangularizacao(struct matriz *L, struct matriz *U)
{
	int n = U->n;
	int j;
	int fator = 8;
	for (int i = 0; i < n; i++)
	{
		for (j = i + 1; (j+fator-1) < n - n % fator; j += fator)
		{
			double m1 = U->mat[j * n + i] / U->mat[i * n + i];
			double m2 = U->mat[(j + 1) * n + i] / U->mat[i * n + i];
			double m3 = U->mat[(j + 2) * n + i] / U->mat[i * n + i];
			double m4 = U->mat[(j + 3) * n + i] / U->mat[i * n + i];
			double m5 = U->mat[(j + 4) * n + i] / U->mat[i * n + i];
			double m6 = U->mat[(j + 5) * n + i] / U->mat[i * n + i];
			double m7 = U->mat[(j + 6) * n + i] / U->mat[i * n + i];
			double m8 = U->mat[(j + 7) * n + i] / U->mat[i * n + i];

			U->mat[j * n + i] = 0.0;
			U->mat[(j + 1) * n + i] = 0.0;
			U->mat[(j + 2) * n + i] = 0.0;
			U->mat[(j + 3) * n + i] = 0.0;
			U->mat[(j + 4) * n + i] = 0.0;
			U->mat[(j + 5) * n + i] = 0.0;
			U->mat[(j + 6) * n + i] = 0.0;
			U->mat[(j + 7) * n + i] = 0.0;
			for (int k = i + 1; k < n; k++)
			{
				U->mat[j * n + k] 		-= U->mat[i * n + k] * m1;
				U->mat[(j + 1) * n + k] -= U->mat[i * n + k] * m2;
				U->mat[(j + 2) * n + k] -= U->mat[i * n + k] * m3;
				U->mat[(j + 3) * n + k] -= U->mat[i * n + k] * m4;
				U->mat[(j + 4) * n + k] -= U->mat[i * n + k] * m5;
				U->mat[(j + 5) * n + k] -= U->mat[i * n + k] * m6;
				U->mat[(j + 6) * n + k] -= U->mat[i * n + k] * m7;
				U->mat[(j + 7) * n + k] -= U->mat[i * n + k] * m8;
			}
			L->mat[j * n + i] 		= m1;
			L->mat[(j + 1) * n + i] = m2;
			L->mat[(j + 2) * n + i] = m3;
			L->mat[(j + 3) * n + i] = m4;
			L->mat[(j + 4) * n + i] = m5;
			L->mat[(j + 5) * n + i] = m6;
			L->mat[(j + 6) * n + i] = m7;
			L->mat[(j + 7) * n + i] = m8;
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

// 			double m1 = U->mat[j * n + i] / U->mat[i * n + i];
// 			double m2 = U->mat[(j + 1) * n + i] / U->mat[i * n + i];
// 			double m3 = U->mat[(j + 2) * n + i] / U->mat[i * n + i];
// 			double m4 = U->mat[(j + 3) * n + i] / U->mat[i * n + i];
// 			double m5 = U->mat[(j + 4) * n + i] / U->mat[i * n + i];
// 			double m6 = U->mat[(j + 5) * n + i] / U->mat[i * n + i];
// 			double m7 = U->mat[(j + 6) * n + i] / U->mat[i * n + i];
// 			double m8 = U->mat[(j + 7) * n + i] / U->mat[i * n + i];

// 			U->mat[j * n + i] = 0.0;
// 			U->mat[(j + 1) * n + i] = 0.0;
// 			U->mat[(j + 2) * n + i] = 0.0;
// 			U->mat[(j + 3) * n + i] = 0.0;
// 			U->mat[(j + 4) * n + i] = 0.0;
// 			U->mat[(j + 5) * n + i] = 0.0;
// 			U->mat[(j + 6) * n + i] = 0.0;
// 			U->mat[(j + 7) * n + i] = 0.0;
// 			for (int k = i + 1; k < n; k++)
// 			{
// 				U->mat[j * n + k] 		-= U->mat[i * n + k] * m1;
// 				U->mat[(j + 1) * n + k] -= U->mat[i * n + k] * m2;
// 				U->mat[(j + 2) * n + k] -= U->mat[i * n + k] * m3;
// 				U->mat[(j + 3) * n + k] -= U->mat[i * n + k] * m4;
// 				U->mat[(j + 4) * n + k] -= U->mat[i * n + k] * m5;
// 				U->mat[(j + 5) * n + k] -= U->mat[i * n + k] * m6;
// 				U->mat[(j + 6) * n + k] -= U->mat[i * n + k] * m7;
// 				U->mat[(j + 7) * n + k] -= U->mat[i * n + k] * m8;
// 			}
// 			L->mat[j * n + i] 		= m1;
// 			L->mat[(j + 1) * n + i] = m2;
// 			L->mat[(j + 2) * n + i] = m3;
// 			L->mat[(j + 3) * n + i] = m4;
// 			L->mat[(j + 4) * n + i] = m5;
// 			L->mat[(j + 5) * n + i] = m6;
// 			L->mat[(j + 6) * n + i] = m7;
// 			L->mat[(j + 7) * n + i] = m8;

// for (k = i + 1; k < n-n%fator; k+=fator){
// 	U->mat[j*n + k] -= U->mat[i*n + k] * m;
// 	U->mat[j*n + k+1] -= U->mat[i*n + k+1] * m;
// 	U->mat[j*n + k+2] -= U->mat[i*n + k+2] * m;
// 	U->mat[j*n + k+3] -= U->mat[i*n + k+3] * m;
// }
// for (k=k; k < n; k++){
// 	U->mat[j*n + k] -= U->mat[i*n + k] * m;
// }

// 		for (int j = i+1; j < n-n%fator; j+=fator)
// 		{
// 			double m1 = U->mat[j*n + i] / U->mat[i*n + i];

// 			U->mat[j*n + i] = 0.0;
// 			for (int k = i + 1; k < n; k++){
// 				U->mat[j*n + k] -= U->mat[i*n + k] * m1;
// 			}
// 			L->mat[j*n + i] = m1;
// 			// segunda
// 			double m2 = U->mat[(j+1)*n + i] / U->mat[i*n + i];

// 			U->mat[(j+1)*n + i] = 0.0;
// 			for (int k = i + 1; k < n; k++){
// 				U->mat[(j+1)*n + k] -= U->mat[i*n + k] * m2;
// 			}
// 			L->mat[(j+1)*n + i] = m2;
// 		}

int encontraMax(struct matriz *M, int c)
{
	float max = 0;
	int n = M->n;
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
	int n = M->n;
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
	int n = M->n;
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
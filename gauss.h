#ifndef __GAUSS__
#define __GAUSS__


/* 
    descrição: 
    paramêtros: 
*/

void triangularizacao(struct matriz *A, struct matriz *L, struct matriz *U, struct matriz *I, int pivoteia, double *tempo);

int encontraMax(struct matriz *M, int l);

double *retrossub(struct matriz *M, double* b, double *tempo);

double *retrossubLower(struct matriz *M, double* b, double *tempo);

double *residuo(struct matriz *M, double *x, double *colId);

double normaL2Residuo(int n, double *res);
#endif
#include <stdio.h>
#include <stdlib.h>

#include "matriz.h"
#include "gauss.h"

struct matriz *montaInterpolacao(struct matriz *x){
    struct matriz *mat;
    int n = x->n;
    mat = alocaMatriz(n, n);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(j == 0){
                mat->mat[i*n + j] = 1;
            } else {
                mat->mat[i*n + j] = mat->mat[i*n + (j-1)] *x->mat[i];
            }
        }
    }

    return mat;
}


int main(){
    int m, n, flag = 0;
    struct matriz *pontos;
    struct matriz *funcs;

    scanf("%d %d", &n, &m);

    pontos = alocaMatriz(1, n);
    funcs = alocaMatriz(m, n);

    leMatriz(pontos);
    leMatriz(funcs);
    for(int i = 0; i < m; i ++){
        struct matriz *L, *U;

        U = montaInterpolacao(pontos);
        L = alocaMatriz(n, n);
        

        if(triangularizacao(L, U) != 0){
        } else {
            // imprimeMatriz(L, stdout);
            // printf("\n");
            // imprimeMatriz(U, stdout);
            // printf("\n");
                
            double *x = NULL, 
            *y = NULL, 
            *b = NULL;
            // pega a coluna da matriz identidade a ser usada como b
            b = pegaLinha(funcs, i);
            
            // acha y (Ly = b)
            flag = retrossubLower(L, b, &y);
            if(!y){
                printf("%d\n", flag);
                free(b);
                break;
            }
            // acha x (Ux = y)
            flag = retrossub(U, y, &x);
            if(!x){
                printf("2: %d\n", flag);
                free(b);
                free(y);
                break;
            }
            for(int j = 0; j < n; j++){
                printf("%0.18lf ", x[j]);
            }
            printf("\n");
            free(b);
            free(x);
            free(y);
        
        }
        

    }

    // fazer LU
    // ta pronto os a
}
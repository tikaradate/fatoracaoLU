#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matriz.h"
#include "gauss.h"

struct matriz *montaInterpolacao(struct matriz *x){
    struct matriz *mat;
    int n = x->n;
    mat = alocaMatriz(n, n);

    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < n; j++){
    //         mat->mat[i*n + j] = pow(x->mat[i], j);
    //     }
    // }
    for(int i = 0; i < n; i++){
         mat->mat[i*n] = 1;
    }

    for(int i = 0; i < n; i++){
        for(int j = 1; j < n; j++){
            mat->mat[i*n + j] = mat->mat[i*n + (j-1)]*x->mat[i];
        }
    }

    return mat;
}


struct matriz *montaAjuste(struct matriz *x){
    struct matriz *kurwa;
    int n = x->n;
    double *somas = calloc(n+n,sizeof(double));
    double *pot  = calloc(n*(n+n),sizeof(double));
    
    
    for(int i = 0; i < n; i++){
        pot[i] = 1;
    }

    for(int i = 1; i < n+n; i++){
        for(int j = 0; j < n; j++){
            // pot[i*n + j] = pot[(i-1)*n + j]*x->mat[j];
            pot[i*n + j] = pow(x->mat[j], i);
        }
    }
    
    // for(int i = 0; i <= n+n; i++){
    //     for(int j = 0; j < n; j++){
    //         printf("%.6lf ",  pot[i*n + j]);
    //     }
    //     printf("\n");
    // }


    // monta o vetor que contém os n+n somatórios
    for(int i = 0; i < n+n; i++){
        for(int j = 0; j < n; j++){
            somas[i] += pot[i*n + j];
            // printf("% .8e ", somas[i]);
        }
        // printf("\n");
    }
    
    kurwa = alocaMatriz(n, n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            kurwa->mat[i*n + j] = somas[i+j];
        }
    }

    free(somas);

    return kurwa;
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
    // interpolacao
    for(int i = 0; i < m; i ++){
        struct matriz *L, *U;

        U = montaInterpolacao(pontos);
        L = alocaMatriz(n, n);
        
        if(triangularizacao(L, U) != 0){
            printf("porra deu diferente de 0?\n");
        } else {
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
                printf("%lf ", x[j]);
            }
            printf("\n");
            free(b);
            free(x);
            free(y);
        
        }
    }
    struct matriz *somatorios;

    somatorios = montaAjuste(pontos);
    
    for(int i = 0; i < m; i ++){
        struct matriz *U = NULL, *L = NULL;
        
        U = alocaMatriz(n, n);
        L = alocaMatriz(n, n);
        copiaMatriz(somatorios, U);
        
        if(triangularizacao(L, U) != 0){
            printf("porra deu diferente de 0?\n");
        } else {
            double *x = NULL;
            double *y = NULL;
            double *b = calloc(n+1, sizeof(double));

            for(int j = 0; j <= n; j++){
                for(int k = 0; k < n; k++){
                    // printf("y_%d = % 0.8f; x^%d = % 0.8f ", k, funcs->mat[i*n + k], j,pow(pontos->mat[k], j));
                    // parece ok pracaralho me fode
                    b[j] += funcs->mat[i*n + k]*pow(pontos->mat[k], j);
                }
                // printf("\n");
            }
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
                printf("%lf ", x[j]);
            }
            printf("\n");
            free(b);
            free(x);
            free(y);
        
        }

    }
}
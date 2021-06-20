#include <stdio.h>
#include "matriz.h"


int main(){
    int n;
    struct matriz *M, *L, *U;

    while(scanf("%d", &n) != EOF){
        M = alocaMatriz(n);
        leMatriz(M);
        // TODO: stuff
        imprimeMatriz(M);
        liberaMatriz(M);
    } 
    return 0;
}
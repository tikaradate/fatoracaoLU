#include <stdio.h>
#include "matriz.h"
#include "argumentos.h"

int main(int argc, char *argv[]){
    int n;
    struct matriz *M, *L, *U;
    struct argumentos args;
    
    args = linha_de_comando(argc, argv);
    
    while(scanf("%d", &n) != EOF){
        M = alocaMatriz(n);
        leMatriz(M);
        // TODO: stuff
        imprimeMatriz(M);
        liberaMatriz(M);
    } 
    return 0;
}
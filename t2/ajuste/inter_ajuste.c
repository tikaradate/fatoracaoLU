#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matriz.h"
#include "gauss.h"
#include "interpolacao.h"
#include "ajuste_curvas.h"

int main(){
    int m, n, flag = 0;
    struct matriz *pontos;
    struct matriz *funcoes;
    struct matriz *somatorios;

    scanf("%d %d", &n, &m);

    pontos = alocaMatriz(1, n);
    funcoes = alocaMatriz(m, n);

    leMatriz(pontos);
    leMatriz(funcoes);
    
    // monta os somatorios utilizado em todo ajuste de curvas
    somatorios = montaAjuste(pontos);
    // interpolacao
    for(int i = 0; i < m; i ++){
        interpola(pontos, funcoes, i);
        ajusta(pontos, funcoes, somatorios, i);
    }
    return 0;
}
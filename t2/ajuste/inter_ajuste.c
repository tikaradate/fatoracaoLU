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
    struct matriz *inter_U, *inter_L;
    struct matriz *ajuste_U, *ajuste_L;

    scanf("%d %d", &n, &m);

    pontos = alocaMatriz(1, n);
    funcoes = alocaMatriz(m, n);

    leMatriz(pontos);
    leMatriz(funcoes);
    
    // SL de interpolação
    inter_U = montaInterpolacao(pontos);
    inter_L = alocaMatriz(n, n);

    if (triangularizacao(inter_L, inter_U) != 0)
    {
        exit(-1);
    }

    // monta os somatorios utilizado em todo ajuste de curvas
    ajuste_U = montaAjuste(pontos);
    ajuste_L = alocaMatriz(n, n);

    
    
    if (triangularizacao(ajuste_L, ajuste_U) != 0)
    {
        exit(-1);
    }

    // interpolacao
    if (triangularizacao_original(ajuste_L, ajuste_U) != 0)
    {
        exit(-1);
    }
    for(int i = 0; i < m; i ++){
        interpola(inter_U, inter_L, funcoes, i);
        ajusta(ajuste_U, ajuste_L, funcoes, pontos, i);
    }
    return 0;
}

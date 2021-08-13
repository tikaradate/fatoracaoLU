#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include<likwid.h>

#include "matriz.h"
#include "gauss.h"
#include "interpolacao.h"
#include "ajuste_curvas.h"

int main(){
    int m, n, flag = 0;
    struct matriz *pontos;
    struct matriz *funcoes;
    struct matriz *somatorios;

    LIKWID_MARKER_INIT;

    scanf("%d %d", &n, &m);

    pontos = alocaMatriz(1, n);
    funcoes = alocaMatriz(m, n);

    leMatriz(pontos);
    leMatriz(funcoes);

    LIKWID_MARKER_START("tabelaAjuste");
    // monta os somatorios utilizado em todo ajuste de curvas
    somatorios = montaAjuste(pontos);
    LIKWID_MARKER_STOP("tabelaAjuste");

    // interpolacao
    for(int i = 0; i < m; i ++){
        interpola(pontos, funcoes, i);
        ajusta(pontos, funcoes, somatorios, i);
    }

    LIKWID_MARKER_CLOSE;

    return 0;
}

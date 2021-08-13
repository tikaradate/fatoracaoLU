#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//#define __LIKWID__
#ifdef __LIKWID__
#include <likwid.h>
#endif

#include "argumentos.h"
#include "matriz.h"
#include "gauss.h"
#include "interpolacao.h"
#include "ajuste_curvas.h"

int main(int argc, char *argv[]){

    #ifdef __LIKWID__
    LIKWID_MARKER_INIT;
    #endif
    struct argumentos args;
    FILE *out;

    int m, n, flag = 0;
    struct matriz *pontos;
    struct matriz *funcoes;
    struct matriz *inter_U, *inter_L;
    struct matriz *ajuste_U, *ajuste_L;
    struct matriz *dummy_U, *dummy_L;

    args = linha_de_comando(argc, argv);
    out = arruma_output(args.output);

    scanf("%d %d", &n, &m);

    pontos = alocaMatriz(1, n);
    funcoes = alocaMatriz(m, n);

    leMatriz(pontos);
    leMatriz(funcoes);
    
    // versão não otimizada da triangularização
    dummy_U = montaInterpolacao(pontos);
    dummy_L = alocaMatriz(n, n);
    #ifdef __LIKWID__
    LIKWID_MARKER_START("triangularizacao_old");
    #endif
    if (triangularizacao_original(dummy_L, dummy_U) != 0)
    {
        exit(-1);
    }
    #ifdef __LIKWID__
    LIKWID_MARKER_STOP("triangularizacao_old");
    #endif

    // SL de interpolação com a versão otimizada da triangularização
    inter_U = montaInterpolacao(pontos);
    inter_L = alocaMatriz(n, n);
    #ifdef __LIKWID__
    LIKWID_MARKER_START("triangularizacao");
    #endif
    if (triangularizacao(inter_L, inter_U) != 0)
    {
        exit(-1);
    }
    #ifdef __LIKWID__
    LIKWID_MARKER_STOP("triangularizacao");
    #endif


    // monta os somatorios utilizado em todo ajuste de curvas
    #ifdef __LIKWID__
    LIKWID_MARKER_START("ajuste");
    #endif
    ajuste_U = montaAjuste(pontos);
    ajuste_L = alocaMatriz(n, n);
    #ifdef __LIKWID__
    LIKWID_MARKER_STOP("ajuste");
    #endif
    
    
    if (triangularizacao(ajuste_L, ajuste_U) != 0)
    {
        exit(-1);
    }

    for(int i = 0; i < m; i ++){
        interpola(inter_U, inter_L, funcoes, i, out);
        ajusta(ajuste_U, ajuste_L, funcoes, pontos, i, out);
    }

    #ifdef __LIKWID__
    LIKWID_MARKER_CLOSE;
    #endif

    return 0;
}

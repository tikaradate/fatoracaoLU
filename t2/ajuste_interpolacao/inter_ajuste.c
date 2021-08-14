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

int padding = 0;

int main(int argc, char *argv[]){

    #ifdef __LIKWID__
    LIKWID_MARKER_INIT;
    #endif
    struct argumentos args;
    FILE *out;

    int m, n, flag = 0;
    struct matriz *pontos;
    struct matriz *funcoes, *funcoes_inter, *funcoes_ajuste, *funcoes_dummy;
    struct matriz *inter_U, *inter_L;
    struct matriz *ajuste_U, *ajuste_L;
    struct matriz *dummy_U, *dummy_L;

    args = linha_de_comando(argc, argv);
    out = arruma_output(args.output);

    scanf("%d %d", &n, &m);

    if (log2(n) - (int) log(2) == 0){
        padding = 1;
        n += padding;
    }
    
    pontos = alocaMatriz(1, n);
    funcoes = alocaMatriz(m, n);

    leMatriz(pontos);
    leMatriz(funcoes);
    
    // versão não otimizada da triangularização
    dummy_U = montaInterpolacao(pontos);
    dummy_L = alocaMatriz(n, n);
    funcoes_dummy = alocaMatriz(m, n);
    copiaMatriz(funcoes, funcoes_dummy);
    #ifdef __LIKWID__
    LIKWID_MARKER_START("triangularizacao_old");
    #endif
    if (triangularizacao_original(dummy_L, dummy_U, funcoes_dummy) != 0)
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

    funcoes_inter = alocaMatriz(m, n);
    copiaMatriz(funcoes, funcoes_inter);
    if (triangularizacao(inter_L, inter_U, funcoes_inter) != 0)
    {
        exit(-1);
    }
    #ifdef __LIKWID__
    LIKWID_MARKER_STOP("triangularizacao");
    #endif

    #ifdef __LIKWID__
    LIKWID_MARKER_START("ajuste");
    #endif
    ajuste_U = montaAjuste(pontos);
    #ifdef __LIKWID__
    LIKWID_MARKER_STOP("ajuste");
    #endif
    ajuste_L = alocaMatriz(n, n);
    
    funcoes_ajuste = alocaMatriz(m, n);
    copiaMatriz(funcoes, funcoes_ajuste);
    if (triangularizacao(ajuste_L, ajuste_U, funcoes_ajuste) != 0)
    {
        exit(-1);
    }

    for(int i = 0; i < m; i ++){
        interpola(inter_U, inter_L, funcoes_inter, i, out);
        ajusta(ajuste_U, ajuste_L, funcoes_ajuste, pontos, i, out);
    }

    #ifdef __LIKWID__
    LIKWID_MARKER_CLOSE;
    #endif
    liberaMatriz(inter_L);
    liberaMatriz(inter_U);
    liberaMatriz(ajuste_L);
    liberaMatriz(ajuste_U);
    liberaMatriz(pontos);
    liberaMatriz(funcoes);

    return 0;
}

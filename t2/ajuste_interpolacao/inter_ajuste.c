#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// necessário para compilar no ambiente de desenvolvimento,
// caso precise das métricas, é descomentado
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
    int m, n;
    struct matriz *pontos;
    struct matriz *funcoes, *funcoes_inter, *funcoes_ajuste, *funcoes_dummy;
    struct matriz *inter_U, *inter_L;
    struct matriz *ajuste_U, *ajuste_L;
    struct matriz *dummy_U, *dummy_L;

    struct argumentos args;
    FILE *out;
    args = linha_de_comando(argc, argv);
    out = arruma_output(args.output);

    if(scanf("%d %d", &n, &m) == EOF){
        fprintf(stderr, "Erro na leitura de tamanho da entrada, abortando...");
        exit(-1);
    }

    pontos = alocaMatriz(1, n);
    funcoes = alocaMatriz(m, n);

    leMatriz(pontos);
    leMatriz(funcoes);
    
    // versão não otimizada da triangularização, apenas para comparação
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
        fprintf(stderr, "Erro na triangularização referente à interpolação, abortando...");
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

    // calcula todos somatórios que envolvem funções e guarda em uma matriz para uso futuro
    for(int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < n; k++)
                funcoes_ajuste->mat[i*n + j] += funcoes->mat[i * n + k] * pow(pontos->mat[k], j);


    if (triangularizacao(ajuste_L, ajuste_U, funcoes_ajuste) != 0)
    {
        fprintf(stderr, "Erro na triangularização referente ao ajuste de curvas, abortando...");
        exit(-1);
    }

    for(int i = 0; i < m; i ++){
        if(interpola(inter_U, inter_L, funcoes_inter, i, out) != 0){
            fprintf(stderr, "Erro na retrossubstituição da interpolação, pulando essa iteração");
        }
        if(ajusta(ajuste_U, ajuste_L, funcoes_ajuste, pontos, i, out) != 0){
            fprintf(stderr, "Erro na retrossubstituição do ajuste de curvas, pulando essa iteração");
        }
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
    liberaMatriz(funcoes_inter);
    liberaMatriz(funcoes_ajuste);

    return 0;
}

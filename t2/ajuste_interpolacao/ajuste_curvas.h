#ifndef __AJUSTE_CURVAS__
#define __AJUSTE_CURVAS__

/* 
    descrição: monta a matriz de coeficientes do ajuste de curvas
    paramêtros: 
        x: os pontos da função
    retorno: a matriz dos coeficientes
*/
struct matriz *montaAjuste(struct matriz *x);

/* 
    descrição: realiza o ajuste de curvas a partir da matriz de coeficientes e dos somatórios com as funções
               e imprime na saída desejada o resultado
    paramêtros: 
        U: matriz Upper gerada
        L: matriz Lower gerada
        funcoes: matriz que contêm os somatórios das funções, os "b"s dos sistemas lineares
        pontos: os pontos recebidos na entrada
        i: a iteração
        out: o stream em que será escrito os dados
    retorno: 0 se tudo certo, -1 se houve algum erro na retrossubstituição, gerando nan ou inf
*/
int ajusta(struct matriz *U, struct matriz *L, struct matriz *funcoes, struct matriz *pontos, int i, FILE *out);

#endif
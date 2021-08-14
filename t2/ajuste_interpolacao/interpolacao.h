#ifndef __INTERPOLACAO__
#define __INTERPOLACAO__

/* 
    descrição: calcula a matriz de interpolação dado os x necessários
    paramêtros: 
        x: os pontos x que serão interpolados
    retorno: a matriz dos coeficientes da interpolação
*/
struct matriz *montaInterpolacao(struct matriz *x);

/* 
    descrição: interpola os pontos a partir da matriz de coeficientes e das funções
               e imprime na saída desejada o resultado
    paramêtros: 
        U: matriz Upper gerada
        L: matriz Lower gerada
        funcoes: matriz que contêm as funções, os "b"s dos sistemas lineares
        pontos: os pontos recebidos na entrada
        i: a iteração
        out: o stream em que será escrito os dados
    retorno: 0 se tudo certo, -1 se houve algum erro na retrossubstituição, gerando nan ou inf
*/
int interpola(struct matriz *U, struct matriz *L, struct matriz *funcoes, int i, FILE *out);

#endif
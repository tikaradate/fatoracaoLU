/*
 * Autores:
 *   Jorge Lucas Vicilli Jabczenski
 *     GRR20190372
 *   Vinicius Tikara Venturi Date
 *     GRR20190367  
 *
 */
#ifndef __ANALISE_ARGS__
#define __ANALISE_ARGS__
#include <stdio.h>

/* 
    atributos:
        output: define o caminho de escrita da saída do programa, 
                de acordo com o argumento de -o
        pivo: carrega a informação se deve ou não ocorrer o pivoteamento parcial, 
              de acordo com o argumento de -p
 */
struct argumentos {
    char *output;
    int pivo;
};

/* 
    descrição: trata os argumentos da linha de comando
    paramêtros: 
        argc: o argc da main
        argv: o argv da main
    retorno: uma instância da struct argumentos devidamente preenchida
*/
struct argumentos linha_de_comando(int argc, char *argv[]);

/* 
    descrição: decide se o output deve ser stdout ou um caminho escolhido
    paramêtros: 
        output: a string que indica aonde serão escritos os dados de saída
    retorno: um FILE* para stdout, se não ouver nada na string, ou um FILE* para
             o caminho indicado pelo argumento output
*/
FILE* arruma_output(char *output);
#endif
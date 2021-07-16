/*
 * Autores:
 *   Jorge Lucas Vicilli Jabczenski
 *     GRR20190372
 *   Vinicius Tikara Venturi Date
 *     GRR20190367  
 *
 */
#include <stdio.h>
#include <math.h>

#include "utils.h"
#include "matriz.h"
#include "gauss.h"
#include "argumentos.h"

int main(int argc, char *argv[])
{
    int n, flag, cont = 0;
    double tempo, tempo_tri,
           tempo_x = 0, 
           tempo_y = 0;
    double *x = NULL, 
           *y = NULL, 
           *b = NULL;
    struct matriz *A, *L, *U, *Id, *Inv;
    struct argumentos args;
    FILE *out;

    // tratamento de argumentos da linha de comando
    args = linha_de_comando(argc, argv);
    out = arruma_output(args.output);
    while (scanf("%d", &n) != EOF)
    {
        fprintf(out, "Ordem: %d\n", n);

        A   = alocaMatriz(n);
        U   = alocaMatriz(n);
        L   = alocaMatriz(n);
        Inv = alocaMatriz(n);
        Id  = alocaMatriz(n);
        // inicilializa diagonal da matriz identidade
        for(int i = 0; i < n; i++){
            Id->m[i][i] = 1; 
        }

        leMatriz(A);
        imprimeMatriz(A, out);
        fprintf(out, "#\n");

        // precisamos preservar a matriz original para o cálculo das normas L2 dos resíduos
        copiaMatriz(A, U);

        // gera as matrizes Lower e Upper
        if(triangularizacao(A, L, U, Id, args.pivo, &tempo_tri) != 0){
            fprintf(stderr, ">>> Matriz gerou resultados inválidos na entrada %d <<<\n", cont);
        }
        else if (!checaInversibilidade(U)){
            fprintf(stderr, ">>> Matriz dada na entrada %d não é inversível <<<\n", cont);
        } else {
            // de coluna em coluna da matriz identidade,
            // resolve os sistemas para obtenção da matriz inversa
            for(int i = 0; i < n; i++){
                // pega a coluna da matriz identidade a ser usada como b
                b = pegaColuna(Id, i);
                // acha y (Ly = b)
                flag = retrossubLower(L, b, &tempo, &y);
                tempo_y += tempo;
                // acha x (Ux = y)
                flag = retrossub(U, y, &tempo, &x);
                tempo_x += tempo;
                // insere a coluna calculada(x) na matriz inversa
                botaColuna(Inv, i, x);
                free(b);
                free(x);
                free(y);
            }
            // checa após o loop pois existem frees
            if(flag != 0){
                fprintf(stderr, ">>> Matriz gerou resultados inválidos na retrossubstituição da entrada %d <<<\n", cont);
            } else {
                imprimeMatriz(Inv, out);
                fprintf(out, "###############\n");
                fprintf(out, "# Tempo Triangularização: %.16lf ms\n"
                            "# Tempo de cálculo do x : %.16lf ms\n"
                            "# Tempo de cálculo do y : %.16lf ms\n",
                        tempo_tri, tempo_x/n, tempo_y/n);
                fprintf(out, "# Valores das %d normas L2 dos resíduos:\n", n);

                // para cada coluna da matriz inversa, calcula a norma L2
                for(int i = 0; i < n; i++){
                    double *res, *colInv, *colId;
                    double *normas = alocaVet(n);

                    colInv = pegaColuna(Inv, i);
                    colId = pegaColuna(Id, i);
                    res = residuo(A, colInv, colId);

                    normas[i] = normaL2Residuo(n, res);
                    fprintf(out, "%.10e ", normas[i]);
                    
                    free(res);
                    free(normas);
                    free(colId);
                    free(colInv);
                }
                fprintf(out, "\n\n");
            }
        }
        // incrementa a quantidade de matrizes já fatoradas
        cont++;
        liberaMatriz(A);
        liberaMatriz(L);
        liberaMatriz(U);
        liberaMatriz(Inv);
        liberaMatriz(Id);
    }

    fclose(out);    
    return 0;
}
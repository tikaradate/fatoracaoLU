#include <stdio.h>
#include <math.h>

#include "utils.h"
#include "matriz.h"
#include "gauss.h"
#include "argumentos.h"

int main(int argc, char *argv[])
{
    int n;
    double tempo, tempo_tri,
           tempo_x = 0, 
           tempo_y = 0;
    double *x, *y, *b;
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
        triangularizacao(A, L, U, Id, args.pivo, &tempo_tri);

        // de coluna em coluna da matriz identidade,
        // resolve os sistemas para obtenção da matriz inversa
        for(int i = 0; i < n; i++){
            // pega a coluna da matriz identidade a ser usada como b
            b = pegaColuna(Id, i);
            // acha y (Ly = b)
            y = retrossubLower(L, b, &tempo);
            tempo_y += tempo;
            // acha x (Ux = y)
            x = retrossub(U, y, &tempo);
            tempo_x += tempo;
            // insere a coluna calculada(x) na matriz inversa
            botaColuna(Inv, i, x);
        }

        imprimeMatriz(Inv, out);
        fprintf(out, "###############\n");
        fprintf(out, "# Tempo Triangularização: %.16lf ms\n"
                     "# Tempo de cálculo do x : %.16lf ms\n"
                     "# Tempo de cálculo do y : %.16lf ms\n",
                tempo_tri, tempo_x/n, tempo_y/n);
        fprintf(out, "# Valores das %d normas L2 dos resíduos:\n", n);

        // para cada coluna da matriz inversa, calcula a norma L2
        for(int i = 0; i < n; i++){
            double *res;
            double *normas = malloc(sizeof(double)*n);
            res = residuo(A, pegaColuna(Inv, i), pegaColuna(Id, i));
            normas[i] = normaL2Residuo(n, res);
            fprintf(out, "%.16lf ", normas[i]);
        }
        fprintf(out, "\n\n");

        liberaMatriz(A);
        liberaMatriz(L);
        liberaMatriz(U);
        liberaMatriz(Inv);
        liberaMatriz(Id);
    }
    fclose(out);    
    return 0;
}
#ifndef __INTERPOLACAO__
#define __INTERPOLACAO__

struct matriz *montaInterpolacao(struct matriz *x);

int interpola(struct matriz *pontos, struct matriz *funcoes, int i);

#endif
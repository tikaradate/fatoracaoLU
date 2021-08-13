#ifndef __AJUSTE_CURVAS__
#define __AJUSTE_CURVAS__

struct matriz *montaAjuste(struct matriz *x);

int ajusta(struct matriz *U, struct matriz *L, struct matriz *funcoes, struct matriz *pontos, int i, FILE *out);
#endif
#ifndef __AJUSTE_CURVAS__
#define __AJUSTE_CURVAS__

struct matriz *montaAjuste(struct matriz *x);

int ajusta(struct matriz *pontos, struct matriz *funcoes, struct matriz *somatorios, int i);

#endif
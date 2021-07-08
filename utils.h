#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdlib.h>
#include <sys/time.h>

#define MAXIT 50

/*  Retorna tempo em milisegundos

    Forma de uso:
 
    double tempo;
    tempo = timestamp();
    <trecho de programa do qual se deseja medir tempo>
    tempo = timestamp() - tempo;
*/

double timestamp(void);

FILE *arruma_output(char *output);
#endif // __UTILS_H__

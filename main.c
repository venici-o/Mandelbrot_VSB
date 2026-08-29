#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include "mandelmath.h"

int main(int argc, char *argv[]) {
    int max_iteracoes = atoi(argv[1]);
    double complex c = -1.5+1*I;
    printf("C = %.1f+%.1fI ;\n", creal(c), cimag(c));
    int it=mandelbrot(c, max_iteracoes);
    printf("\nIteracoes: %d", it);
    return 0;
}
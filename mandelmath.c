#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include "mandelmath.h"

//Arquivo com funções relacionadas à iteração o set

int mandelbrot(double complex c, int max_iteracoes){
    double complex z = 0;

    for (int i = 0;i<max_iteracoes;i++){
        z = (z * z) + c;
        printf("\nZ%d = (%.2f)+(%.2fI)\n", i, creal(z), cimag(z));
        if (cabs(z)>2){
            printf("Fora! Valor Absoluto: %.5f\n", (cabs(z)));
            return i;
        }
    }
    return 0;
}
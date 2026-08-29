#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <omp.h>
#include <pthread.h>
#include "header.h"

//Arquivo com funções relacionadas à iteração o set

int mandelbrot(double complex c, int max_iteracoes){
    double complex z = 0;
    int i;

    for (i=0;i<max_iteracoes;i++){
        z = (z * z) + c;
        printf("\nZ%d = (%.2f)+(%.2fI)\n", i, creal(z), cimag(z));
        if (cabs(z)>2){
            return max_iteracoes;
        }
    }
    return i;
}


float calc_c(int altura_atual, int largura_atual, int altura_total, int largura_total){
    float cx = (altura_atual/altura_total);
    // EU TENHO QUE IMPLEMENTAR UMA FUNCAO QUE FAÇA O C PRA CADA MOMENTO DO GRAFICO;
    // X PRO REAL, Y PRO IMAGINARIO; A CADA MOMENTO TEM QUE PEGAR ISSO, 
    // MULTIPLICAR CADA UM PELO FATOR DE ALTERAÇÃO 
    // ( ((MAX_REAL)-(MIN_REAL)*X) pro incremento real & (MAX_IMAG)-(MIN_IMAG)*X pro incremento imaginario) 
    // E TRANSFORMAR NUM COMPLEX DOUBLE
    // IMPORTANTE PACAS!!!!!!!
}

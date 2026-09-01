#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <omp.h>
#include <pthread.h>
#include "header.h"
#include <time.h>
#include <stdint.h>


//Arquivo com funções relacionadas à iteração o set

int mandelbrot(double complex c, int max_iteracoes){
    double complex z = 0;
    int i;

    for (i=0;i<max_iteracoes;i++){
        z = (z * z) + c;
        if (cabs(z)>2){
            return i+1;
        }
    }
    return max_iteracoes;
}

double complex calc_c(int largura_atual, int altura_atual, float incremento_x, float incremento_y){
    double 
    real_c = MIN_REAL + incremento_x * largura_atual,
    imag_c = MIN_IMG + incremento_y * altura_atual;
    return CMPLX(real_c, imag_c);
}

int intensity(int iteracoes, int max_iteracoes){
    int color = (255/(float)max_iteracoes)*iteracoes;
    return color;
}


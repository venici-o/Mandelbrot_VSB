#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <omp.h>
#include <pthread.h>
#include "header.h"

//Arquivo com funções relacionadas à geração gráfica

float intensity(int iteracoes, int max_iteracoes){
    float color = (255/max_iteracoes)*iteracoes;
    return color;
}

/*
void graph_serial(int altura, int largura, int max_iteracoes){
    for (int i=0;i<altura;i++){
        for (int j=0; j<largura; j++){
            float c = calc_c(i, j, altura, largura);
            int iteracoes=mandelbrot(c, max_iteracoes);
        
        }

    }
}
*/
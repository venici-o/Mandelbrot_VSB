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
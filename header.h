#ifndef MATHS_H
#define MATHS_H

#include <complex.h>
#include <omp.h>
#include <pthread.h>
#include <time.h>
#include <stdint.h>
#include <pthread.h>

#define MAX_REAL 1.0
#define MIN_REAL -2.0
#define MAX_IMG 1.5
#define MIN_IMG -1.5

int mandelbrot(double complex c, int max_iteracoes);
float intensity(int iteracoes, int max_iteracoes);
double complex calc_c(int largura_atual, int altura_atual, float incremento_x, float incremento_y);
int exec_serial(int altura, int largura, float incremento_x, float incremento_y, int max_iteracoes);
int exec_openmp(int altura, int largura, float incremento_x, float incremento_y, int max_iteracoes, int num_threads);

#endif
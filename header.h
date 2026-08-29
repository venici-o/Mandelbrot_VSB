#ifndef MATHS_H
#define MATHS_H

#include <complex.h>
#include <omp.h>
#include <pthread.h>

#define MAX_REAL = 1
#define MIN_REAL = -2
#define MAX_IMG = 1.5
#define MIN_IMG = -1.5

int mandelbrot(double complex c, int max_iteracoes);
float intensity(int iteracoes, int max_iteracoes);
float getc(int altura_atual, int largura_atual, int altura_total, int largura_total);

#endif
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <omp.h>
#include <pthread.h>
#include "header.h"
#include <time.h>
#include <stdint.h>

int main(int argc, char *argv[]) {


    if (argc!=5){
        fprintf(stderr,"[ERRO]Quantidade de argumentos inválida! A formatação deve ser:\n-> ./mandelbrot [largura] [altura] [max_iteracoes] [num_threads]");
        return -1;
    }

    int largura = (atoi(argv[1])),
    altura = (atoi(argv[2]));

    if (largura<1||altura<1){
        fprintf(stderr,"ERRO: A altura e a largura devem ser inteiros maiores que 0!");
        return -1;
    }

    int max_iteracoes = atoi(argv[3]);

    if (max_iteracoes<1){
        fprintf(stderr,"[ERRO] Quantidade de Iterações Inválida");
        return -1;
    }

    int num_threads = atoi(argv[4]);

    if (num_threads<1){
        fprintf(stderr,"[ERRO] O processo deve usar ao menos 1 thread.");
        return -1;
    }

    float incremento_x= (MAX_REAL-MIN_REAL)/(largura);
    float incremento_y= (MAX_IMG-MIN_IMG)/(altura);
    double 
        valor_serial,
        valor_openmp,
        valor_pthread1,
        valor_pthread2;

    //Execução Serial
    if (exec_serial(altura, largura, incremento_x, incremento_y, max_iteracoes, &valor_serial) != 0) {
    return -1;
    }

    //Execução OpenPM
    if (exec_openmp(altura, largura, incremento_x, incremento_y, max_iteracoes, num_threads, &valor_openmp) != 0) {
    return -1;
    }

    //Execução Pthreads 1
    if (exec_pthreads1(altura, largura, incremento_x, incremento_y, max_iteracoes, num_threads, &valor_pthread1) != 0) {
    return -1;
    }

    //Execução Pthreads 2
    if (exec_pthreads2(altura, largura, incremento_x, incremento_y, max_iteracoes, num_threads, &valor_pthread2) != 0) {
    return -1;
    }

    FILE *fp = fopen("times.txt", "w");
    if (fp==NULL){
        fprintf(stderr, "[ERRO] Não foi possível abrir o arquivo.");
        return -1;
    }
    
    fprintf(fp,"Serial: %.6fs\n", valor_serial);
    fprintf(fp,"OpenMP: %.6fs\n", valor_openmp);
    fprintf(fp,"Pthreads1: %.6fs\n", valor_pthread1);
    fprintf(fp,"Pthreads2: %.6fs\n", valor_pthread2);
    fclose(fp);
    
    return 0;
}
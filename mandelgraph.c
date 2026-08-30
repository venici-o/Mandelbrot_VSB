#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <omp.h>
#include <pthread.h>
#include "header.h"
#include <time.h>

//Arquivo com funções relacionadas à geração gráfica

float intensity(int iteracoes, int max_iteracoes){
    float color = (255/(float)max_iteracoes)*iteracoes;
    return color;
}

int exec_serial(int altura, int largura, float incremento_x, float incremento_y, int max_iteracoes){
    struct timespec inicio;
    struct timespec fim;
    int *save= (int *)malloc(largura*altura*sizeof(int));
    if (save==NULL){
        fprintf(stderr, "[ERRO] Não foi possível alocar a memória.");
        return -1;
    }

    FILE *fp = fopen("mandelbrot_vsb_serial.pgm", "w");
    if (fp==NULL){
        fprintf(stderr, "[ERRO] Não foi possível abrir o arquivo.");
        free(save);
        return -1;
        
    }

    int current_iteracoes;
    float current_pixel;
    double complex current_c;
    
    clock_gettime(CLOCK_MONOTONIC, &inicio);
    for (int i = 0;i<altura;i++){
        for (int j = 0;j<largura;j++){
    
            current_c = calc_c(j,i,incremento_x,incremento_y);
            current_iteracoes = mandelbrot(current_c, max_iteracoes);
            current_pixel = intensity(current_iteracoes, max_iteracoes);
            save[largura*i + j] = current_pixel;
    
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &fim);

    for (int i = 0;i<altura;i++){
        for (int j = 0;j<largura;j++){
            fprintf(fp,"%d ", save[largura*i + j]);
        }
    
        fprintf(fp,"\n");
    }
    
    fclose(fp);
    free (save);
    double exec_time_serial = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1000000000.0;
    
    printf ("Tempo de Duração: %.9f", exec_time_serial);
    return 0;
}


int exec_openpm(int altura, int largura, float incremento_x, float incremento_y, int max_iteracoes, int num_threads){

}
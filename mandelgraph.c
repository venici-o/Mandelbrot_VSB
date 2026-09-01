#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <omp.h>
#include <pthread.h>
#include "header.h"
#include <time.h>

//Arquivo com funções relacionadas à geração gráfica
typedef struct {
    int id;
    int num_threads;
    int max_iteracoes;
    int largura;
    int altura;
    float incremento_x;
    float incremento_y;
    int *save;
} DataThread;

int intensity(int iteracoes, int max_iteracoes){
    int color = (255/(float)max_iteracoes)*iteracoes;
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
    int current_pixel;
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
    
    printf ("Serial: %.9f\n", exec_time_serial);
    return 0;
}

//OpenMP
int exec_openmp(int altura, int largura, float incremento_x, float incremento_y, int max_iteracoes, int num_threads){
    struct timespec inicio;
    struct timespec fim;

    int *save= (int *)malloc(largura*altura*sizeof(int));
    if (save==NULL){
        fprintf(stderr, "[ERRO] Não foi possível alocar a memória.");
        return -1;
    }

    FILE *fp = fopen("mandelbrot_vsb_openmp.pgm", "w");
    if (fp==NULL){
        fprintf(stderr, "[ERRO] Não foi possível abrir o arquivo.");
        free(save);
        return -1;
        
    }

    clock_gettime(CLOCK_MONOTONIC, &inicio);
    // nota pra caso eu apresente: aparentemente, com menor quantidade de pixels,
    // o serial é melhor do que com threading
    #pragma omp parallel for num_threads(num_threads) schedule(dynamic)
    for (int i = 0;i<altura;i++){
        for (int j = 0;j<largura;j++){
    
            double complex current_c = calc_c(j,i,incremento_x,incremento_y);
            int current_iteracoes = mandelbrot(current_c, max_iteracoes);
            int current_pixel = intensity(current_iteracoes, max_iteracoes);
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
    double exec_time_openmp = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1000000000.0;
    
    printf ("OpenMP: %.9f\n", exec_time_openmp);
    return 0;
}

//Pthreads; Workblock
void *workblock(void *arg){
    DataThread *data = (DataThread *)arg;
    
    int thread_inicio = data->id*data->altura / data->num_threads;
    int thread_fim = (data->id+1)*data->altura / data->num_threads;

    for (int i = thread_inicio; i < thread_fim; i++){
        for (int j = 0; j < data->largura; j++){
            double complex current_c = calc_c(j,i,data->incremento_x,data->incremento_y);
            int current_iteracoes = mandelbrot(current_c, data->max_iteracoes);
            int current_pixel = intensity(current_iteracoes, data->max_iteracoes);
            data->save[data->largura*i + j] = current_pixel;
        }   
    }

    return NULL;
}

//Pthread 1
int exec_pthreads(int altura, int largura, float incremento_x, float incremento_y, int max_iteracoes, int num_threads){
    struct timespec inicio;
    struct timespec fim;

    pthread_t *pthreads= malloc(num_threads * sizeof(pthread_t));
    if (pthreads==NULL){
        fprintf(stderr,"[ERRO] Não foi possível alocar memória para as threads!");
        free(pthreads);
    }

    DataThread *data_threads= malloc(num_threads * sizeof(DataThread));
    if (data_threads==NULL){
        fprintf(stderr,"[ERRO] Não foi possível alocar memória para as threads!");
        free(pthreads);
        free(data_threads);
    }

    int *save= (int *)malloc(largura*altura*sizeof(int));
    if (save==NULL){
        fprintf(stderr, "[ERRO] Não foi possível alocar a memória.");
        return -1;
    }

    for (int i=0;i<num_threads;i++){
        data_threads[i].id=i;
        data_threads[i].altura=altura;
        data_threads[i].largura=largura;
        data_threads[i].incremento_x=incremento_x;
        data_threads[i].incremento_y=incremento_y;
        data_threads[i].max_iteracoes=max_iteracoes;
        data_threads[i].num_threads=num_threads;
        data_threads[i].save=save;
    }

    FILE *fp = fopen("mandelbrot_vsb_pthread1.pgm", "w");
    if (fp==NULL){
        fprintf(stderr, "[ERRO] Não foi possível abrir o arquivo.");
        free(save);
        return -1;
        
    }

    clock_gettime(CLOCK_MONOTONIC, &inicio);
    
    for (int i=0; i<num_threads; i++){
        int chamada = pthread_create(&pthreads[i], NULL, workblock, &data_threads[i]);

    if (chamada!=0){
        fprintf(stderr, "[ERRO] Falha ao tentar criar Pthreads.");
        return -1;
        }
    }

    for (int i = 0; i < num_threads; i++){
        pthread_join(pthreads[i], NULL);
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
    free(pthreads);
    free(data_threads);
    double exec_time_pthread1 = (fim.tv_sec - inicio.tv_sec) + (fim.tv_nsec - inicio.tv_nsec) / 1000000000.0;
    
    printf ("Pthread 1: %.9f\n", exec_time_pthread1);
    return 0;
}


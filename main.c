#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <omp.h>
#include <pthread.h>
#include "header.h"

int main(int argc, char *argv[]) {

/*
    if (argc!=5){
        printf("[ERRO]Quantidade de argumentos inválida! A formatação deve ser:\n");
        printf("-> ./mandelbrot [largura] [altura] [max_iteracoes] [num_threads]");
        return -1;
    }
*/
    int largura = (atoi(argv[1])),
    altura = (atoi(argv[2]));

    if (largura<1||altura<1){
        printf("ERRO: A altura e a largura devem ser inteiros maiores que 0!");
    }

    int max_iteracoes = atoi(argv[3]);

    if (max_iteracoes<1){
        printf("[ERRO] Quantidade de Iterações Inválida! Deve haver ao menos uma iteração.");
        return -1;
    }

    float incremento_x= (MAX_REAL-MIN_REAL)/(largura-1);
    float incremento_y= (MAX_IMG-MIN_IMG)/(altura-1);
    
    //exemplo de serial
    FILE *fp = fopen("mandelbrot_mla_serial.pgm", "w");
    if (fp==NULL){
        fprintf(stderr, "[ERRO]Não foi possível abrir o arquivo");
        return -1;
    }

    int current_iteracoes;
    float current_pixel;
    double complex current_c;
    
    for (int i = 0;i<altura;i++){
        for (int j = 0;j<largura;j++){
    
            current_c = calc_c(j,i,incremento_x,incremento_y);
            current_iteracoes = mandelbrot(current_c, max_iteracoes);
            current_pixel = intensity(current_iteracoes, max_iteracoes);
            fprintf(fp,"%d ", ((int)current_pixel));
    
        }
    
        fprintf(fp,"\n");
    }
    
    fclose(fp);

    return 0;
}
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
    double complex current;
    for (int i = 0;i<altura;i++){
        for (int j = 0;j<largura;j++){
            current = calc_c(j,i,incremento_x,incremento_y);
            printf("(%d, %d) C = %.2f + %.2f I", j, i, creal(current), cimag(current));
        }
        printf("\n");
    }


    return 0;
}
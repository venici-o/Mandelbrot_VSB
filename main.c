#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <omp.h>
#include <pthread.h>
#include "header.h"

int main(int argc, char *argv[]) {
    
    if (argc!=5){
        printf("[ERRO]Quantidade de argumentos inválida! A formatação deve ser:\n");
        printf("-> ./mandelbrot [largura] [altura] [max_iteracoes] [num_threads]");
        return -1;
    }

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

    
    for (int i=0;i<altura;i++){
        for (int j=0; j<largura; j++){
            float c = getc(i, j, altura, largura);
            int iteracoes=mandelbrot(c, max_iteracoes);
        
        }

    }
    return 0;
}
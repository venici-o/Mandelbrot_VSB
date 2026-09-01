# Mandelbrot — Implementação com Threads

Trabalho da disciplina de Infraestrutura de Software que gera o conjunto de
Mandelbrot utilizando quatro estratégias: serial, OpenMP e duas implementações
com Pthreads.

## Compilação

```bash
make
```

## Execução

```bash
./mandelbrot <largura> <altura> <max_iteracoes> <num_threads>
```

Exemplo:

```bash
./mandelbrot 800 600 1000 4
```

O programa gera quatro arquivos `.pgm`, um para cada estratégia, e registra os
tempos de execução no arquivo `times.txt`.

## Limpeza

```bash
make clean
```

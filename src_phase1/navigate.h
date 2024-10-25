#ifndef NAVIGATE_H
#define NAVIGATE_H

#include <stdlib.h>
#include <stdio.h>


#define FIND_MAX 1
#define SUM_POSITIVES 2

// Encontra o valor de linhas e colunas máximo
void find_largest_grid(FILE *fp, int *maxRows, int *maxCols);

// Constrói a maior grelha
int **grid_builder(int maxRows, int maxCols);

// Liberta a grelha
void free_grid(int** grid, int rows);

// Função que processa as grelhas 
void process_grids(FILE *fp, int** grid, char *solutionName);

// Função que encontra o caminho
int bfs_modular(int **grid, int rows, int cols, int startX, int startY, int kstep, int taskType);

// Função que move o para o destino
void move_to_destination(FILE *output, int **grid, int rows, int cols, int startRow, int startCol, int destRow, int destCol);

#endif
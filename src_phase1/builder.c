#include "navigate.h"

// Função que encontra o valor de linhas e colunas máximo
void find_largest_grid(FILE *fp, int *maxRows, int *maxCols) {
    int rows, cols, initrows, initcols, kstep;
    int destRow = 0, destCol = 0;
    int grid_numbers, temp, count = 0;
    
    // Loop que percorre o ficheiro e encontra o valor máximo de linhas e colunas
    while(fscanf(fp, "%d %d %d %d %d", &rows, &cols, &initrows, &initcols, &kstep) == 5) {

        if (kstep == 0) {
            if (fscanf(fp, "%d %d", &destRow, &destCol) != 2) {
                exit(0);
            }
        }
        
        if (rows > *maxRows) *maxRows = rows;

        if (cols > *maxCols) *maxCols = cols;

        grid_numbers = rows * cols;

        while (count < grid_numbers && fscanf(fp, "%d", &temp) == 1){
            count++;
        }
        count = 0;
    }
    rewind(fp);

    return;
}

// Função que constrói a maior grelha
int **grid_builder(int maxRows, int maxCols) {

    int** grid = (int**)malloc(maxRows * sizeof(int*)); // Aloca a memória para cada linha

    if (grid == NULL) exit(0);

    for (int i = 0; i < maxRows; i++) {
        grid[i] = (int*)malloc(maxCols * sizeof(int)); // Aloca a memória para cada coluna
        if (grid[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(grid[j]); 
            }
            free(grid);
            exit(0);
        }
    }

    return grid;
}

// Função que liberta a grelha
void free_grid(int** grid, int rows) {
    for (int i = 0; i < rows; i++) {
        free(grid[i]); 
    }
    free(grid); 
}
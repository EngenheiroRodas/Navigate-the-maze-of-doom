#include <string.h>

#include "navigate.h"

int main(int argc, char *argv[]) {
    const char *inputExtension = ".1maps";
    const char *solExtension = ".sol1maps";
    
    int maxRows = -1, maxCols = -1;
    int **grid;
    FILE *fp;
    char *solName, *inputFile = argv[1];
    
    // Verifica que o número de argumentos é um só (Nome do ficheiro)
    if (argc != 2) {
        exit(0);
    }

    // Verifica se o ficheiro tem a extensão correta
    char *dot = strrchr(inputFile, '.');
    if (dot == NULL || strcmp(dot, inputExtension) != 0) {
        exit(0);
    }

    // Aloca memória para o nome do ficheiro de output
    solName = malloc(strlen(inputFile) + 4);
    if (solName == NULL) {
        exit(0);
    }

    // Copia o nome do ficheiro e adiciona a extensão .sol1maps
    strncpy(solName, inputFile, dot - inputFile);
    solName[dot - inputFile] = '\0';  
    strcat(solName, solExtension);    

    // Abre o ficheiro de input
    fp = fopen(inputFile, "r");
    if (fp == NULL) {
        free(solName);  
        exit(0);
    }

    // Processa o ficheiro
    find_largest_grid(fp, &maxRows, &maxCols);
    grid = grid_builder(maxRows, maxCols);
    process_grids(fp, grid, solName);
    free_grid(grid, maxRows);

    // Fecha o ficheiro e liberta a memória
    free(solName);
    fclose(fp);

    return 0;
}

#include "navigate.h"

// Função que processa as grelhas
void process_grids(FILE *fp, int** grid, char *solutionName) {
    FILE *output;
    int rows, cols, initrows, initcols, kstep;
    int destRow = 0, destCol = 0;
    int result;

    output = fopen(solutionName, "w");
    if (output == NULL)
        exit(0);

    // Enquanto houver dados para processar
    while (fscanf(fp, "%d %d %d %d %d", &rows, &cols, &initrows, &initcols, &kstep) == 5) {
        
        if (kstep == 0) {
            if (fscanf(fp, "%d %d", &destRow, &destCol) != 2) {
                exit(0);
            }
        }

        // Copia os valores para a grelha
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (fscanf(fp, "%d", &grid[i][j]) != 1) {
                    exit(0);
                }
            }
        }

        if (kstep) { // Tarefa 1 e 2
            if (initrows < 1 || initrows > rows || initcols < 1 || initcols > cols) {
                fprintf(output, "%d %d %d %d %d\n\n", rows, cols, initrows, initcols, kstep);
                continue;
            } else {
                if (kstep < 0) { // Tarefa 1 
                    result = bfs_modular(grid, rows, cols, initrows, initcols, kstep, FIND_MAX);
                    fprintf(output, "%d %d %d %d %d %d\n\n", rows, cols, initrows, initcols, kstep, result);
                }
                else if (kstep > 0) { // Tarefa 2
                    result = bfs_modular(grid, rows, cols, initrows, initcols, kstep, SUM_POSITIVES);
                    fprintf(output, "%d %d %d %d %d %d\n\n", rows, cols, initrows, initcols, kstep, result);
                }
            }
        } else { // Tarefa 3
            if (initrows < 1 || initrows > rows || initcols < 1 || initcols > cols || destRow < 1 || destRow > rows || destCol < 1 || destCol > cols) {
                fprintf(output, "%d %d %d %d 0 %d %d\n\n", rows, cols, initrows, initcols, destRow, destCol);
                continue;
            } else{
            move_to_destination(output, grid, rows, cols, initrows, initcols, destRow, destCol);
            }
        }
        
       
    }
    fclose(output);
}
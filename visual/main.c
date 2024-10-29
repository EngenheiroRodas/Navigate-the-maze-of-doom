#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "graph.h"

/*****************************************************************************
 * main ()
 *
 * Arguments: argc, argv
 *
 * Returns: result of the selected task 
 *
 * Description: Navigate a map of LxC, with a given starting point (l0, c0) with k steps, 
 *              all parameters are read from the first line of the input file 
 *
 ****************************************************************************/

int main(int argc, char *argv[]) {
    int rows, cols, targetEnergy, initrows, initcols, kstep, initEnergy, bestFinalEnergy, temp;  

    Node *root = NULL;

    if (argc != 2) {
        printf("Usage: %s <input file>\n", argv[0]);
        return 1;
    }

    // Load the graph from the input file
    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror("Failed to open file");
        return 1;
    }

    // Processes the input file 
    while (fscanf(fp, "%d %d %d %d %d %d %d", &rows, &cols, &targetEnergy, &initrows, &initcols, &kstep, &initEnergy) == 7) {
        root = build_graph(fp, rows, cols, initrows, initcols, kstep);  
        
        free_graph(root); 
    }
    
    // Closes the file and frees all memory allocated 
    fclose(fp);

    return 0;
}

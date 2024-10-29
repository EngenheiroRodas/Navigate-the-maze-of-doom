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
    const char *inputExtension = ".maps";
    const char *solExtension = ".solmaps";
    char *solName, *inputFile = argv[1];
    bool foundPath = false;

    Node *root = NULL;
    FILE *fp, *output;

    // Verifies the program only recieves one argument
    if (argc != 2) {
        exit(0);
    }

    // Verifies if the input file has the correct extension
    char *dot = strrchr(inputFile, '.');
    if (dot == NULL || strcmp(dot, inputExtension) != 0) {
        exit(0);
    }

    // Allocates memory for the output file name
    solName = malloc(strlen(inputFile) + 4);
    if (solName == NULL) {
        exit(0);
    }

    // Copies the input file name to the output file name and changes the extension to .solmaps
    strncpy(solName, inputFile, dot - inputFile);
    solName[dot - inputFile] = '\0';  
    strcat(solName, solExtension);    

    // Opens the input file
    fp = fopen(inputFile, "r");
    if (fp == NULL) {
        free(solName);  
        exit(0);
    }

    // Opens the output file
    output = fopen(solName, "w");
    if (output == NULL) {
       fclose(fp);
       free(solName);
       exit(0);
    }

    // Processes the input file 
    while (fscanf(fp, "%d %d %d %d %d %d %d", &rows, &cols, &targetEnergy, &initrows, &initcols, &kstep, &initEnergy) == 7) {
        root = build_graph(fp, rows, cols, initrows, initcols, kstep);  
        
        free_graph(root); 
    }
    
    // Closes the file and frees all memory allocated 
    free(solName);
    fclose(fp);
    fclose(output);

    return 0;
}

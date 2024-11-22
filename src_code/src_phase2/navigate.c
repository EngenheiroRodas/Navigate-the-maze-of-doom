#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "graph.h"
#include "stack.h"

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
    Stack *stack = NULL;
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
        
        // Verifies if the input file has the legal values 
        if ((targetEnergy <= 0 && targetEnergy != -2) || initrows < 1 || initrows > rows || initcols < 1 || initcols > cols || kstep <= 0 || initEnergy <= 0) { 
            fprintf(output, "%d %d %d %d %d %d %d\n\n", rows, cols, targetEnergy, initrows, initcols, kstep, initEnergy);
            for (int i = 0; i < rows * cols; i++) {
                if (fscanf(fp, "%d", &temp) != 1) {
                    exit(0);
                }
            }
            continue;
        }
        // The given parameters are valid but the problem has no solution 
        if (kstep >= rows * cols) { 
            fprintf(output, "%d %d %d %d %d %d %d -1\n\n", rows, cols, targetEnergy, initrows, initcols, kstep, initEnergy);
            for (int i = 0; i < rows * cols; i++) {
                if (fscanf(fp, "%d", &temp) != 1) {
                    exit(0);
                }
            }
            continue;
        }
        
        // Builds the graph
        root = build_graph(fp, rows, cols, initrows, initcols, kstep);  
        
        // Creates the stack to store the path found so far 
        stack = createStack(kstep + 1);  

        // Task 1
        if (targetEnergy >= 1) {
            // If a valid path is found, print it
            if ((foundPath = dfsT1(root, stack, kstep, initEnergy, targetEnergy))) {
                print_found_path(output, stack, rows, cols, targetEnergy, initrows, initcols, kstep, initEnergy);
            } 
            // Problem has no solution
            else {
                fprintf(output, "%d %d %d %d %d %d %d -1\n\n", rows, cols, targetEnergy, initrows, initcols, kstep, initEnergy);  // No valid path found
            }

        } 
        // Task 2    
        else if (targetEnergy == -2) {
            // Creates the stack to store the best path found so far
            Stack* bestStack = createStack(kstep + 1);  
            // Set to a low value to find the maximum 
            bestFinalEnergy = -10000;

            // If a valid path is found, print it
            if ((foundPath = dfsT2(root, stack, bestStack, kstep, initEnergy, &bestFinalEnergy))) {
                print_found_path(output, bestStack, rows, cols, targetEnergy, initrows, initcols, kstep, initEnergy);
            }
            // Problem has no solution
             else {
                fprintf(output, "%d %d %d %d %d %d %d -1\n\n", rows, cols, targetEnergy, initrows, initcols, kstep, initEnergy);  // No valid path found
            }

            // Cleans the stack which containts the best found paths 
            deleteStack(bestStack); 
        }
        
        // Cleans the stack which containts the path found and the graph  
        deleteStack(stack); 
        free_graph(root); 
       
    }
    
    // Closes the file and frees all memory allocated 
    free(solName);
    fclose(fp);
    fclose(output);

    return 0;
}

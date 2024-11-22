#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "graph.h"

struct node_ {
    int row, col;     
    int energy;      
    bool visited;      
    struct node_ *up, *down, *left, *right;  
};

/*****************************************************************************
 * create_node ()
 *
 * Arguments: row - row of the node
 *            col - column of the node
 *            energy - energy value of the node
 *            
 * Returns: newNode
 *
 * Description: This function creates a new node  
 ****************************************************************************/

Node* create_node(int row, int col, int energy) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        exit(0);
    }


    newNode->row = row;
    newNode->col = col;
    newNode->energy = energy;
    newNode->visited = false;  
    newNode->up = newNode->down = newNode->left = newNode->right = NULL;

    return newNode;
}

/*****************************************************************************
 * build_graph ()
 *
 * Arguments: fp- file pointer to the input file
 *            rows- number of rows in the grid, read from the input file   
 *            cols- number of columns in the grid, read from the input file
 *            initRow- initial row of the starting point, read from the input file
 *            initCol- initial column of the starting point, read from the input file
 *            kstep- ammount of steps avaliable to move, read from the input file
 *
 * Returns: Node* root
 *
 * Description: This function reads the input file and builds a graph based on the input file 
 ****************************************************************************/

Node* build_graph(FILE *fp, int rows, int cols, int initRow, int initCol, int kstep) {
    int value, relRow, relCol;
    Node *root = NULL;

    int minRow, maxRow, minCol, maxCol;

    // Bound the kstep based on the grid dimensions
    if (kstep > rows + cols - 1) kstep = rows + cols - 1;

    // Calculate bounds for rows and columns within the kstep range
    minRow = (initRow - kstep < 1) ? 1 : initRow - kstep;
    maxRow = (initRow + kstep > rows) ? rows : initRow + kstep;
    minCol = (initCol - kstep < 1) ? 1 : initCol - kstep;
    maxCol = (initCol + kstep > cols) ? cols : initCol + kstep;

    // Create a temporary matrix for nodes within the kstep range
    Node ***node_matrix = (Node ***)malloc((maxRow - minRow + 1) * sizeof(Node **));  

    for (int i = 0; i <= (maxRow - minRow); i++) {
        node_matrix[i] = (Node **)malloc((maxCol - minCol + 1) * sizeof(Node *));
        for (int j = 0; j <= (maxCol - minCol); j++) {
            node_matrix[i][j] = NULL;  
        }
    }

    // Read the file sequentially, row by row, column by column
    for (int row = 1; row <= rows; row++) {
        for (int col = 1; col <= cols; col++) {
            if (fscanf(fp, "%d", &value) != 1) {
                exit(0);  // Handle errors in input reading
            }

            // Calculate relative position in node_matrix
            relRow = row - minRow;  // Offset based on minRow
            relCol = col - minCol;  // Offset based on minCol

            // Check if (row, col) is within the Manhattan distance (kstep) from the starting point
            if (abs(initRow - row) + abs(initCol - col) <= kstep) {
                // Create the node only if it's within the kstep range
                Node *newNode = create_node(row, col, value);
                node_matrix[relRow][relCol] = newNode;  // Store node in relative matrix

                // Link the node to its neighbors
                if (relRow > 0 && node_matrix[relRow - 1][relCol]) {  
                    newNode->up = node_matrix[relRow - 1][relCol];
                    node_matrix[relRow - 1][relCol]->down = newNode;
                }
                if (relCol > 0 && node_matrix[relRow][relCol - 1]) {  
                    newNode->left = node_matrix[relRow][relCol - 1];
                    node_matrix[relRow][relCol - 1]->right = newNode;
                }

                // Set the root node if this is the initial position
                if (row == initRow && col == initCol) {
                    root = newNode;
                }
            }
        }
    }
    // Free the temporary node matrix
    for (int i = 0; i <= (maxRow - minRow); i++) {
        free(node_matrix[i]);
    }
    // Free the temporary matrix
    free(node_matrix);

    return root;  
}

/*****************************************************************************
 * free_line ()
 *
 * Arguments: node - the first node of the line
 *
 * Returns: board - the allocated board structure
 *
 * Description: frees the memory allocated for a line of nodes
 *           
 ****************************************************************************/

void free_line(Node *node) {
    Node *aux;

    while (node->left) {
        node = node->left;
    }

    while (node->right) {
        aux = node;
        node = node->right;
        free(aux);
    }
    free(node);
}

/*****************************************************************************
 * free_graph ()
 *
 * Arguments: node - the first node of the graph
 *
 * Returns: (void)
 *
 * Description: frees the memory allocated for the entire graph
 *           
 ****************************************************************************/

void free_graph(Node *node) {
    Node *aux;

    while (node->up) node = node->up;

    while (node->down) {
        aux = node;
        node = node->down;
        free_line(aux);
    }
    free_line(node);
}

/*****************************************************************************
 * print_found_path ()
 *
 * Arguments: output - file pointer to the output file
 *            stack - stack containing the path to be printed
 *            rows - number of rows in the grid
 *            cols - number of columns in the grid
 *            targetEnergy - target energy value
 *            initRow - initial row of the starting point
 *            initCol - initial column of the starting point
 *            kstep - ammount of steps avaliable to move
 *            initEnergy - initial energy value
 *
 * Returns: (void)
 *
 * Description: prints the path found by the search algorithm
 *           
 ****************************************************************************/

void calculate_sum(Stack* stack, int *sum) {
    if (isEmpty(stack)) {
        return;
    }

    Node *aux = pop(stack);
    if (returnIndex(stack) != -1) { // Exclude root node from sum calculation
        *sum += aux->energy;
    }

    calculate_sum(stack, sum);

    // Push back to maintain original stack order
    push(stack, aux);
}

void print_path_recursive(FILE *output, Stack* stack) {
    if (isEmpty(stack)) {
        return;
    }

    Node *aux = pop(stack);

    // Recursive call to print the rest of the stack in correct order
    print_path_recursive(output, stack);

    // Print only if it is not the root node
    if (returnIndex(stack) != -1) {
        fprintf(output, "%d %d %d\n", aux->row, aux->col, aux->energy);
    }

    // Push the node back to the stack to preserve original stack order
    push(stack, aux);
}

void print_found_path(FILE *output, Stack* stack, int rows, int cols, int targetEnergy, int initRow, int initCol, int kstep, int initEnergy) {
    int sum = initEnergy;

    // Calculate the sum first without including the root node
    calculate_sum(stack, &sum);

    // Print the first line of the output file with the sum
    fprintf(output, "%d %d %d %d %d %d %d %d\n", rows, cols, targetEnergy, initRow, initCol, kstep, initEnergy, sum);

    // Use recursive function to print path in correct order, excluding the root node
    print_path_recursive(output, stack);

    // Add newline at the end
    fprintf(output, "\n");

    return;
}

/*****************************************************************************
 * sum_or_max ()  
 *
 * Arguments: currentNode - the first node of the line
 *            stepsLeft - number of steps left to move      
 *            biggerInt - pointer to the biggest integer found  
 *
 * Returns: sum_line
 * 
 * Description: This function calculates the sum of the energy values of the nodes in a line
 *              or finds the biggest integer in the line
 *              
 ****************************************************************************/

int sum_or_max(Node *currentNode, int stepsLeft, int *biggerInt) {
    int sumLine = 0, auxSteps = stepsLeft;
    Node *aux = currentNode;

    while (aux->left && auxSteps > 0) {
        aux = aux->left;
        if (aux->energy > 0 && aux->visited == 0) {
            if (aux->energy > *biggerInt) {
                *biggerInt = aux->energy;
            }
            sumLine += aux->energy;            
        }
        auxSteps--;
    }

    if (currentNode->energy > 0 && currentNode->visited == 0) {
        if (currentNode->energy > *biggerInt) {
            *biggerInt = currentNode->energy;
        }
        sumLine += currentNode->energy;
    }

    auxSteps = stepsLeft;

    while (currentNode->right && auxSteps > 0) {
        currentNode = currentNode->right;
        if (currentNode->energy > 0 && currentNode->visited == 0) {
            if (currentNode->energy > *biggerInt) {
                *biggerInt = currentNode->energy;
            }
            sumLine += currentNode->energy;
        }
        auxSteps--;
    }

    if (sumLine > (*biggerInt) * stepsLeft && *biggerInt != 0 && stepsLeft > 0) {
        return (*biggerInt) * stepsLeft;
    } else {
        return sumLine;
    }
}

/*****************************************************************************
 * best_Bound ()  
 *
 * Arguments: currentNode - the first node of the line
 *            stepsLeft - number of steps left to move      
 *
 * Returns: sum
 * 
 * Description: This function calculates the best bound for the energy values of the nodes 
 *              
 ****************************************************************************/

int best_Bound(Node *currentNode, int stepsLeft) {
    int biggerInt = 0;
    int sum = 0, auxSteps = stepsLeft;
    Node *aux = currentNode;

    while (aux->up && auxSteps > 0) {
        aux = aux->up;
        auxSteps--;
        sum += sum_or_max(aux, auxSteps, &biggerInt);
    }

    sum += sum_or_max(currentNode, stepsLeft, &biggerInt);

    while (currentNode->down && stepsLeft > 0) {
        currentNode = currentNode->down;
        stepsLeft--;
        sum += sum_or_max(currentNode, stepsLeft, &biggerInt);
    }

    return sum;
}

/*****************************************************************************
 * dfsT1 ()  
 *
 * Arguments: currentNode - the first node of the line
 *            stack - stack containing the path
 *            stepsLeft - number of steps left to move
 *            energy - current energy value
 *            targetEnergy - target energy value
 *
 * Returns: bool
 * 
 * Description: This function performs a depth-first search to find a path with the target energy value
 *              
 ****************************************************************************/

bool dfsT1(Node* currentNode, Stack* stack, int stepsLeft, int energy, int targetEnergy) {
    // Base case: If energy is below 1, this path is invalid.
    if (energy < 1) {
        return false;
    }
    //Bound used to ensure time efficiency
    int potentialEnergy = best_Bound(currentNode, stepsLeft);
    if (potentialEnergy + energy < targetEnergy) {
        return false;
    }

    // If we have no steps left, check if we reached the target energy
    if (stepsLeft == 0) {
        if (energy >= targetEnergy) {
            // Push the final node onto the stack before returning
            push(stack, currentNode);
            return true;
        }
        return false;
    }

    // Push the current node onto the stack (for backtracking)
    push(stack, currentNode);

    // Mark the current node as visited
    currentNode->visited = true;

    // Explore in all 4 directions (up, down, left, right)
    Node* neighbors[4] = {currentNode->up, currentNode->down, currentNode->left, currentNode->right};
    for (int i = 0; i < 4; i++) {
        if (neighbors[i] && !neighbors[i]->visited) {
            if(dfsT1(neighbors[i], stack, stepsLeft - 1, energy + neighbors[i]->energy, targetEnergy)){
                return true;
            }
        }
    }
    // Backtrack: unmark the node and pop it from the stack
    currentNode->visited = false;
    pop(stack);  

    // If we reached here, no valid path was found in this direction
    return false;
}

/*****************************************************************************
 * dfsT2 ()  
 *
 * Arguments: currentNode - the first node of the line
 *            stack - stack containing the path
 *            bestStack - stack containing the best path found
 *            stepsLeft - number of steps left to move
 *            energy - current energy value
 *            bestFinalEnergy - pointer to the best final energy found
 *
 * Returns: bool
 * 
 * Description: This function performs a depth-first search to find the path with the highest final energy
 *              
 ****************************************************************************/

bool dfsT2(Node* currentNode, Stack* stack, Stack* bestStack, int stepsLeft, int energy, int* bestFinalEnergy) {
    // Base case: If energy is below 1, this path is invalid.
    if (energy < 1) {
        return false;
    }

    // Bound used to ensure time efficency 
    int potentialEnergy = best_Bound(currentNode, stepsLeft);
    if (potentialEnergy + energy < *bestFinalEnergy) {
        return false;
    } 

    // If we have no steps left, check if this path has the highest final energy.
    if (stepsLeft == 0) {
        if (energy > *bestFinalEnergy) {
            *bestFinalEnergy = energy;  // Update the best final energy

            // Save the best path by copying the current stack into bestStack.
            copyStack(stack, bestStack);

            // Pushes the final node to the bestStack
            push(bestStack, currentNode);  
        }
        return true;  
    }

    // Push the current node onto the stack (for backtracking)
    push(stack, currentNode);

    // Mark the current node as visited
    currentNode->visited = true;

    // Define a list of neighbors to explore
    Node* neighbors[4] = {currentNode->up, currentNode->down, currentNode->left, currentNode->right};
    bool foundPath = false;
    for (int i = 0; i < 4; i++) {
        if (neighbors[i] && !neighbors[i]->visited) {
            foundPath |= dfsT2(neighbors[i], stack, bestStack, stepsLeft - 1, energy + neighbors[i]->energy, bestFinalEnergy);
        }
    }
    // Backtrack: unmark the node and pop it from the stack
    currentNode->visited = false;
    pop(stack); 

    return foundPath;
}
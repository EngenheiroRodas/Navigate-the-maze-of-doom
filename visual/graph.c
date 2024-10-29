#include "graph.h"

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
        perror("Error while creating node!");
        exit(1);
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
                perror("Error reading value!");
                exit(1);  // Handle errors in input reading
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
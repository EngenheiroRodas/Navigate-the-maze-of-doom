#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct node_ {
    int row, col;     
    int energy;      
    bool visited;
    struct node_ *up, *down, *left, *right;  
}Node;

Node* build_graph(FILE *fp, int rows, int cols, int initRow, int initCol, int kstep);

Node* create_node(int row, int col, int energy);

void free_graph(Node *node);

#endif
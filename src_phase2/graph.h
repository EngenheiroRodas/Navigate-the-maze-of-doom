#ifndef GRAPH_H
#define GRAPH_H

#include "stack.h"

Node* build_graph(FILE *fp, int rows, int cols, int initRow, int initCol, int kstep);

Node* create_node(int row, int col, int energy);

void free_graph(Node *node);

bool dfsT1(Node* currentNode, Stack* stack, int stepsLeft, int energy, int targetEnergy);

bool dfsT2(Node* currentNode, Stack* stack, Stack* bestStack, int stepsLeft, int energy, int *bestFinalEnergy);

void print_found_path(FILE *output, Stack* stack, int rows, int cols, int targetEnergy, int initRow, int initCol, int kstep, int initEnergy);

#endif
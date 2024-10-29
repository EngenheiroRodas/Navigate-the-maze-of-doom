#ifndef GRAPH_H
#define GRAPH_H

typedef struct node_ Node;

Node* build_graph(FILE *fp, int rows, int cols, int initRow, int initCol, int kstep);

Node* create_node(int row, int col, int energy);

void free_graph(Node *node);

#endif
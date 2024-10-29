#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include "graph.h"

// Draw the entire graph as 3D spheres
void draw_graph(Node *root);

// Reset visited status for all nodes
void reset_visited(Node *node);

#endif

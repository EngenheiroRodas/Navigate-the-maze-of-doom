#include <GL/glut.h>
#include <stdbool.h>
#include "visualization.h"
#include "graph.h"

// Define min and max sphere sizes for scaling based on energy
const float MIN_RADIUS = 0.5f;
const float MAX_RADIUS = 2.0f;

// Function to map energy to sphere radius
float energy_to_radius(int energy) {
    int min_energy = -10;   // Set this according to your data range
    int max_energy = 50;    // Set this according to your data range

    // Clamp energy within the range
    if (energy < min_energy) energy = min_energy;
    if (energy > max_energy) energy = max_energy;

    return MIN_RADIUS + (MAX_RADIUS - MIN_RADIUS) * (float)(energy - min_energy) / (max_energy - min_energy);
}

// Recursive function to draw each node as a sphere
void draw_node(Node *node, float x, float y, float z, float spacing) {
    if (!node || node->visited) return;  // Avoid re-rendering visited nodes
    node->visited = true;

    // Map energy to sphere radius
    float radius = energy_to_radius(node->energy);

    glPushMatrix();
    glTranslatef(x, y, z);
    glutSolidSphere(radius, 20, 20);  // Draw sphere for node
    glPopMatrix();

    // Recursively draw neighbors
    float offset = spacing;
    draw_node(node->up, x, y + offset, z, spacing);
    draw_node(node->down, x, y - offset, z, spacing);
    draw_node(node->left, x - offset, y, z, spacing);
    draw_node(node->right, x + offset, y, z, spacing);
}

// Wrapper function to reset node visit status and call draw_node
void draw_graph(Node *root) {
    if (!root) return;

    // Reset visited status for all nodes before drawing
    reset_visited(root);

    // Start drawing from root node
    draw_node(root, 0.0f, 0.0f, 0.0f, 5.0f);
}

// Helper function to reset visited status for all nodes
void reset_visited(Node *node) {
    if (!node || !node->visited) return;

    node->visited = false;
    reset_visited(node->up);
    reset_visited(node->down);
    reset_visited(node->left);
    reset_visited(node->right);
}

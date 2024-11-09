#include <GL/glut.h>
#include <stdbool.h>
#include <math.h>
#include "visualization.h"
#include "graph.h"


// Define min and max sphere sizes for scaling based on energy
const float MIN_RADIUS = 0.5f;
const float MAX_RADIUS = 2.0f;

// Custom colors
const float START_COLOR[3] = {1.0f, 0.0f, 0.0f}; // Red for start node

// Function to map energy to sphere radius
float energy_to_radius(int energy) {
    int min_energy = -10;   // Set this according to your data range
    int max_energy = 50;    // Set this according to your data range

    if (energy < min_energy) energy = min_energy;
    if (energy > max_energy) energy = max_energy;

    return MIN_RADIUS + (MAX_RADIUS - MIN_RADIUS) * (float)(energy - min_energy) / (max_energy - min_energy);
}

// Function to determine node color based on energy
void set_node_color(int energy, bool isStartNode) {
    if (isStartNode) {
        glColor3fv(START_COLOR);  // Red for start node
    } else if (energy >= 0) {
        glColor3f(0.5f, 0.8f, 1.0f);  // Blue for positive energy
    } else {
        glColor3f(0.5f, 1.0f, 0.5f);  // Green for negative energy
    }
}

// Function to draw an edge as a 3D cylinder
void draw_edge(float x1, float y1, float z1, float x2, float y2, float z2, int energy) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float dz = z2 - z1;
    float distance = sqrt(dx * dx + dy * dy + dz * dz);

    glPushMatrix();
    glTranslatef(x1, y1, z1);

    // Set edge color to match node based on energy
    if (energy >= 0) {
        glColor3f(0.5f, 0.8f, 1.0f);  // Blue for positive
    } else {
        glColor3f(0.5f, 1.0f, 0.5f);  // Green for negative
    }

    // Rotate cylinder to align with the direction of the edge
    float angle = acos(dz / distance) * 180.0 / M_PI;
    float axisX = -dy;
    float axisY = dx;
    glRotatef(angle, axisX, axisY, 0.0);

    GLUquadric *quad = gluNewQuadric();
    gluCylinder(quad, 0.2, 0.2, distance, 10, 10);  // Adjust thickness with cylinder radius
    gluDeleteQuadric(quad);

    glPopMatrix();
}

// Draw node and edges with modified colors and thickness
void draw_node(Node *node, float x, float y, float z, float spacing, bool isStartNode) {
    if (!node || node->visited) return;
    node->visited = true;

    // Set color based on node's energy level
    set_node_color(node->energy, isStartNode);

    // Draw the node as a sphere
    float radius = energy_to_radius(node->energy);
    glPushMatrix();
    glTranslatef(x, y, z);
    glutSolidSphere(radius, 20, 20);  // Draw sphere for node
    glPopMatrix();

    // Draw edges with thickness and color
    float offset = spacing;
    if (node->up) {
        draw_edge(x, y, z, x, y + offset, z, node->energy);
        draw_node(node->up, x, y + offset, z, spacing, false);
    }
    if (node->down) {
        draw_edge(x, y, z, x, y - offset, z, node->energy);
        draw_node(node->down, x, y - offset, z, spacing, false);
    }
    if (node->left) {
        draw_edge(x, y, z, x - offset, y, z, node->energy);
        draw_node(node->left, x - offset, y, z, spacing, false);
    }
    if (node->right) {
        draw_edge(x, y, z, x + offset, y, z, node->energy);
        draw_node(node->right, x + offset, y, z, spacing, false);
    }
}

// Wrapper function to reset node visit status and call draw_node
void draw_graph(Node *root) {
    if (!root) return;

    reset_visited(root);
    draw_node(root, 0.0f, 0.0f, 0.0f, 5.0f, true);  // Start from the root node
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

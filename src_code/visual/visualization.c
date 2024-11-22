#include <GL/glut.h>
#include <math.h>
#include "visualization.h"
#include "graph.h"

float energy_to_radius(int energy) {
    int min_energy = -10, max_energy = 50;

    if (energy < min_energy) energy = min_energy;
    if (energy > max_energy) energy = max_energy;
    return 0.5f + (2.0f - 0.5f) * (float)(energy - min_energy) / (max_energy - min_energy);
}

void set_node_color(int energy, bool isStartNode) {
    if (isStartNode) {
        glColor3f(1.0f, 0.84f, 0.0f);
    } else if (energy >= 0) {
        glColor3f(0.29f, 0.56f, 0.89f);
    } else {
        glColor3f(0.31f, 0.72f, 0.28f);
    }
}

void draw_edge(float x1, float y1, float z1, float x2, float y2, float z2) {
    float dx = x2 - x1, dy = y2 - y1, dz = z2 - z1;
    float distance = sqrt(dx * dx + dy * dy + dz * dz);
    float angle = acos(dz / distance) * 180.0 / M_PI;

    glColor3f(0.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(x1, y1, z1);

    glRotatef(angle, -dy, dx, 0.0);
    GLUquadric *quad = gluNewQuadric();
    gluCylinder(quad, 0.2, 0.2, distance, 10, 10);
    gluDeleteQuadric(quad);
    glPopMatrix();
}

void draw_node(Node *node, float x, float y, float z, float spacing, bool isStartNode) {
    float radius;

    if (!node || node->visited) return;
    node->visited = true;

    set_node_color(node->energy, isStartNode);
    radius = energy_to_radius(node->energy);

    glPushMatrix();
    glTranslatef(x, y, z);
    glutSolidSphere(radius, 20, 20);
    glPopMatrix();

    if (node->up) {
        draw_edge(x, y, z, x, y + spacing, z);
        draw_node(node->up, x, y + spacing, z, spacing, false);
    }
    if (node->down) {
        draw_edge(x, y, z, x, y - spacing, z);
        draw_node(node->down, x, y - spacing, z, spacing, false);
    }
    if (node->left) {
        draw_edge(x, y, z, x - spacing, y, z);
        draw_node(node->left, x - spacing, y, z, spacing, false);
    }
    if (node->right) {
        draw_edge(x, y, z, x + spacing, y, z);
        draw_node(node->right, x + spacing, y, z, spacing, false);
    }
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

void draw_graph(Node *root) {
    if (!root) return;

    reset_visited(root);
    draw_node(root, 0.0f, 0.0f, 0.0f, 5.0f, true);
}
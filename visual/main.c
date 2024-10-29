#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "visualization.h"

int window_width = 800;
int window_height = 600;
Node *root = NULL;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Set up camera
    gluLookAt(0, 0, 100, 0, 0, 0, 0, 1, 0);

    // Draw graph as 3D spheres
    draw_graph(root);

    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / (double)height, 1.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
}

/*****************************************************************************
 * main ()
 ****************************************************************************/

int main(int argc, char *argv[]) {
    int rows, cols, targetEnergy, initrows, initcols, kstep, initEnergy;

    if (argc != 2) {
        printf("Usage: %s <input file>\n", argv[0]);
        return 1;
    }

    // Load the graph from the input file
    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror("Failed to open file");
        return 1;
    }

    // Read input file and build the graph
    if (fscanf(fp, "%d %d %d %d %d %d %d", &rows, &cols, &targetEnergy, &initrows, &initcols, &kstep, &initEnergy) == 7) {
        root = build_graph(fp, rows, cols, initrows, initcols, kstep);
    }
    fclose(fp);

    if (!root) {
        printf("Failed to build graph\n");
        return 1;
    }

    // OpenGL/GLUT Initialization
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(window_width, window_height);
    glutCreateWindow("Graph Visualizer");

    // Register OpenGL callbacks
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    // Set up basic OpenGL settings
    glEnable(GL_DEPTH_TEST);

    // Start the main loop
    glutMainLoop();

    // Free graph after the display loop is closed
    free_graph(root);

    return 0;
}

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "visualization.h"

int window_width = 800;
int window_height = 600;
Node *root = NULL;

// Initial camera settings
float zoom = -50.0f;          // Distance of the camera from the origin
float rotationX = 0.0f;       // Rotation around X-axis
float rotationY = 0.0f;       // Rotation around Y-axis
float cameraPosX = 0.0f;      // Camera position X
float cameraPosY = 0.0f;      // Camera position Y

int lastMouseX, lastMouseY;   // Store the last mouse position for dragging
bool isRightMouseButton = false; // Track if the right mouse button is pressed

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Set up camera with zoom, rotation, and translation
    glTranslatef(cameraPosX, cameraPosY, zoom);  // Zoom and translate camera
    glRotatef(rotationX, 1.0f, 0.0f, 0.0f);     // Rotate around X-axis
    glRotatef(rotationY, 0.0f, 1.0f, 0.0f);     // Rotate around Y-axis

    // Draw graph as 3D spheres
    draw_graph(root);

    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / (double)height, 1.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
}

// Handle mouse scroll for zooming
void mouseWheel(int button, int dir, int x, int y) {
    if (dir > 0) {
        zoom += 5.0f;  // Zoom in
    } else {
        zoom -= 5.0f;  // Zoom out
    }
    glutPostRedisplay();  // Request redisplay
}

// Handle mouse drag for rotation and translation
void mouseMotion(int x, int y) {
    int dx = x - lastMouseX;
    int dy = y - lastMouseY;

    if (isRightMouseButton) {
        // Translate camera with right mouse button drag
        cameraPosX += dx * 0.05f;   // Adjust sensitivity as needed
        cameraPosY -= dy * 0.05f;
    } else {
        // Rotate camera with left mouse button drag
        rotationX += dy * 0.2f;
        rotationY += dx * 0.2f;
    }

    lastMouseX = x;
    lastMouseY = y;

    glutPostRedisplay();  // Request redisplay
}

// Track initial mouse position when button is pressed
void mouseButton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        lastMouseX = x;
        lastMouseY = y;
        isRightMouseButton = false;  // Left button: rotate
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        lastMouseX = x;
        lastMouseY = y;
        isRightMouseButton = true;   // Right button: translate
    }

    // Detect scroll wheel action (may vary by system; often uses middle button up/down codes)
    if (button == 3) {  // Scroll up
        zoom += 5.0f;
    } else if (button == 4) {  // Scroll down
        zoom -= 5.0f;
    }
    glutPostRedisplay();  // Request redisplay
}

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
    glutMouseFunc(mouseButton);     // Track mouse button state for dragging
    glutMotionFunc(mouseMotion);    // Track mouse motion for rotation/translation

    // Set up basic OpenGL settings
    glEnable(GL_DEPTH_TEST);

    // Start the main loop
    glutMainLoop();

    // Free graph after the display loop is closed
    free_graph(root);

    return 0;
}

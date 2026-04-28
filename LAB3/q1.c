#include <GL/freeglut.h>
#include <math.h>

int segments = 20;   // initial smoothness
float radius = 0.5;

// Draw filled circle using triangle fan
void drawCircle() {
    glBegin(GL_TRIANGLE_FAN);

    // Center vertex (RED)
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(0.0, 0.0);

    // Perimeter vertices (BLUE)
    glColor3f(0.0, 0.0, 1.0);

    for (int i = 0; i <= segments; i++) {
        float theta = 2.0f * 3.1416f * i / segments;
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        glVertex2f(x, y);
    }

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawCircle();
    glFlush();
}

// Handle arrow keys
void specialKeys(int key, int x, int y) {
    if (key == GLUT_KEY_UP) {
        segments += 2;
    }
    else if (key == GLUT_KEY_DOWN) {
        if (segments > 3)
            segments -= 2;
    }

    glutPostRedisplay();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Parametric Circle - Triangle Fan");

    init();
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);

    glutMainLoop();
    return 0;
}
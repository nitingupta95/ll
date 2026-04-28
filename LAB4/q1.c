#include <GL/freeglut.h>
#include <math.h>

void drawCircle(float cx, float cy, float r) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float theta = i * 3.1416 / 180;
        glVertex2f(cx + r * cos(theta), cy + r * sin(theta));
    }
    glEnd();
}

void drawText(float x, float y, char *str) {
    glRasterPos2f(x, y);
    for (int i = 0; str[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, str[i]);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // ===== Cargo Body (lower, bigger) =====
    glColor3f(0, 0, 1); // Blue
    glBegin(GL_POLYGON);
    glVertex2f(-0.2, -0.2);
    glVertex2f(0.7, -0.2);
    glVertex2f(0.7, -0.6);
    glVertex2f(-0.2, -0.6);
    glEnd();

    // ===== Cabin (higher than cargo) =====
    glColor3f(1, 0, 0); // Red
    glBegin(GL_POLYGON);
    glVertex2f(-0.7, -0.05);
    glVertex2f(-0.2, -0.05);
    glVertex2f(-0.2, -0.6);
    glVertex2f(-0.7, -0.6);
    glEnd();

    // ===== Wheels =====
    glColor3f(0.2, 0.2, 0.2);
    drawCircle(-0.4, -0.7, 0.1);
    drawCircle(0.4, -0.7, 0.1);

    // ===== Road =====
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(-1, -0.85);
    glVertex2f(1, -0.85);
    glEnd();

    // ===== Text (Centered in Cargo) =====
    glColor3f(1, 1, 1); // White
    drawText(0.05, -0.42, "DELIVERY");

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Better Truck");

    gluOrtho2D(-1, 1, -1, 1);

    glutDisplayFunc(display);
    glutMainLoop();
}
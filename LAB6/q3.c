#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>

int x1, y1_, x2, y2;

void plot(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void bresenham(int x1, int y1_, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1_);

    int sx = (x2 > x1) ? 1 : -1;
    int sy = (y2 > y1_) ? 1 : -1;

    int x = x1;
    int y = y1_;

    plot(x, y);

    // Case 1: |slope| < 1
    if (dx > dy) {
        int p = 2 * dy - dx;

        for (int i = 0; i < dx; i++) {
            x += sx;

            if (p < 0) {
                p += 2 * dy;
            } else {
                y += sy;
                p += 2 * (dy - dx);
            }

            plot(x, y);
        }
    }
    // Case 2: |slope| >= 1
    else {
        int p = 2 * dx - dy;

        for (int i = 0; i < dy; i++) {
            y += sy;

            if (p < 0) {
                p += 2 * dx;
            } else {
                x += sx;
                p += 2 * (dx - dy);
            }

            plot(x, y);
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1, 0, 0);
    bresenham(x1, y1_, x2, y2);

    glFlush();
}

int main(int argc, char** argv) {
    printf("Enter x1 y1_ x2 y2: ");
    scanf("%d %d %d %d", &x1, &y1_, &x2, &y2);

    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Bresenham Line Drawing");

    gluOrtho2D(0, 500, 0, 500);

    glPointSize(3);

    glutDisplayFunc(display);
    glutMainLoop();
}
#include <GL/freeglut.h>
#include <stdio.h>

float xmin = 2, ymin = 2, xmax = 4, ymax = 4;
float x1, y1_, x2, y2;

int liangBarsky(float *x1, float *y1_, float *x2, float *y2) {
    float p[4], q[4];
    float u1 = 0.0, u2 = 1.0;

    float dx = *x2 - *x1;
    float dy = *y2 - *y1_;

    p[0] = -dx; q[0] = *x1 - xmin;
    p[1] = dx;  q[1] = xmax - *x1;
    p[2] = -dy; q[2] = *y1_ - ymin;
    p[3] = dy;  q[3] = ymax - *y1_;

    for (int i = 0; i < 4; i++) {
        if (p[i] == 0) {
            if (q[i] < 0) return 0;
        } else {
            float t = q[i] / p[i];

            if (p[i] < 0) {
                if (t > u1) u1 = t;
            } else {
                if (t < u2) u2 = t;
            }
        }
    }

    if (u1 > u2) return 0;

    float nx1 = *x1 + u1 * dx;
    float ny1_ = *y1_ + u1 * dy;
    float nx2 = *x1 + u2 * dx;
    float ny2 = *y1_ + u2 * dy;

    *x1 = nx1;
    *y1_ = ny1_;
    *x2 = nx2;
    *y2 = ny2;

    if (u1 == 0 && u2 == 1) {
        printf("Line is completely inside\n");
    } else {
        printf("Line is intersecting\n");
    }

    return 1;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw clipping window
    glColor3f(0, 1, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();

    // Original line (Red)
    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(x1, y1_);
    glVertex2f(x2, y2);
    glEnd();

    // Clipped line
    float cx1 = x1, cy1_ = y1_, cx2 = x2, cy2 = y2;

    if (liangBarsky(&cx1, &cy1_, &cx2, &cy2)) {
        glColor3f(0, 0, 1);
        glBegin(GL_LINES);
        glVertex2f(cx1, cy1_);
        glVertex2f(cx2, cy2);
        glEnd();
    } else {
        printf("Line is completely outside\n");
    }

    glFlush();
}

int main(int argc, char** argv) {
    printf("Enter x1 y1_ x2 y2: ");
    scanf("%f %f %f %f", &x1, &y1_, &x2, &y2);

    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Liang Barsky Line Clipping");

    gluOrtho2D(0, 6, 0, 6);

    glutDisplayFunc(display);
    glutMainLoop();
}
#include <GL/freeglut.h>
#include <stdio.h>

float xmin, ymin, xmax, ymax;
float x1, y1_, x2, y2;

#define INSIDE 0
#define LEFT   1
#define RIGHT  2
#define BOTTOM 4
#define TOP    8

int computeCode(float x, float y) {
    int code = INSIDE;

    if (x < xmin) code |= LEFT;
    else if (x > xmax) code |= RIGHT;

    if (y < ymin) code |= BOTTOM;
    else if (y > ymax) code |= TOP;

    return code;
}

void cohenSutherland() {
    float x, y;
    int code1 = computeCode(x1, y1_);
    int code2 = computeCode(x2, y2);
    int accept = 0;

    while (1) {
        if ((code1 == 0) && (code2 == 0)) {
            printf("Line is completely inside\n");
            accept = 1;
            break;
        }
        else if (code1 & code2) {
            printf("Line is completely outside\n");
            break;
        }
        else {
            printf("Line is intersecting\n");

            int code_out = code1 ? code1 : code2;

            if (code_out & TOP) {
                x = x1 + (x2 - x1) * (ymax - y1_) / (y2 - y1_);
                y = ymax;
            }
            else if (code_out & BOTTOM) {
                x = x1 + (x2 - x1) * (ymin - y1_) / (y2 - y1_);
                y = ymin;
            }
            else if (code_out & RIGHT) {
                y = y1_ + (y2 - y1_) * (xmax - x1) / (x2 - x1);
                x = xmax;
            }
            else if (code_out & LEFT) {
                y = y1_ + (y2 - y1_) * (xmin - x1) / (x2 - x1);
                x = xmin;
            }

            if (code_out == code1) {
                x1 = x;
                y1_ = y;
                code1 = computeCode(x1, y1_);
            } else {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }

    if (accept) {
        glColor3f(0, 1, 0);
        glBegin(GL_LINES);
        glVertex2f(x1, y1_);
        glVertex2f(x2, y2);
        glEnd();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Window (Clipping Rectangle)
    glColor3f(0, 1, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();

    // Original Line
    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(x1, y1_);
    glVertex2f(x2, y2);
    glEnd();

    // Clipped Line
    cohenSutherland();

    glFlush();
}

int main(int argc, char** argv) {
    printf("Enter x1 y1_ x2 y2: ");
    scanf("%f %f %f %f", &x1, &y1_, &x2, &y2);

    printf("Enter xmin ymin xmax ymax: ");
    scanf("%f %f %f %f", &xmin, &ymin, &xmax, &ymax);

    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Cohen Sutherland Line Clipping");

    gluOrtho2D(0, 500, 0, 500);

    glutDisplayFunc(display);
    glutMainLoop();
}
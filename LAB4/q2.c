#include <GL/freeglut.h>
#include <math.h>

void drawCircle(float r, float R, float G, float B) {
    glColor3f(R, G, B);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float theta = i * 3.1416 / 180;
        glVertex2f(r * cos(theta), r * sin(theta));
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    float radius = 0.8;

    // Colors: White, Black, Blue, Red, Yellow
    float colors[5][3] = {
        {1,1,1},
        {0,0,0},
        {0,0,1},
        {1,0,0},
        {1,1,0}
    };

    for (int i = 0; i < 5; i++) {
        drawCircle(radius, colors[i][0], colors[i][1], colors[i][2]);
        radius -= 0.15;
    }

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Target");

    gluOrtho2D(-1, 1, -1, 1);

    glutDisplayFunc(display);
    glutMainLoop();
}
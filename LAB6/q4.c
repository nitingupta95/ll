#include <GL/freeglut.h>
#include <math.h>

float triangle[3][2] = {
    {100, 100},
    {200, 100},
    {150, 200}
};

float angle = 45; // degrees

void drawTriangle(float t[3][2]) {
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 3; i++) {
        glVertex2f(t[i][0], t[i][1]);
    }
    glEnd();
}

void rotateOrigin(float src[3][2], float dest[3][2]) {
    float rad = angle * 3.1416 / 180;

    for (int i = 0; i < 3; i++) {
        dest[i][0] = src[i][0]*cos(rad) - src[i][1]*sin(rad);
        dest[i][1] = src[i][0]*sin(rad) + src[i][1]*cos(rad);
    }
}

void rotatePoint(float src[3][2], float dest[3][2], float h, float k) {
    float rad = angle * 3.1416 / 180;

    for (int i = 0; i < 3; i++) {
        float x = src[i][0] - h;
        float y = src[i][1] - k;

        float xr = x*cos(rad) - y*sin(rad);
        float yr = x*sin(rad) + y*cos(rad);

        dest[i][0] = xr + h;
        dest[i][1] = yr + k;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    float t_origin[3][2];
    float t_point[3][2];

    // Original (Saffron)
    glColor3f(1.0, 0.5, 0.0);
    drawTriangle(triangle);

    // Rotate about origin (White)
    rotateOrigin(triangle, t_origin);
    glColor3f(1, 1, 1);
    drawTriangle(t_origin);

    // Rotate about first vertex (Green)
    rotatePoint(triangle, t_point, triangle[0][0], triangle[0][1]);
    glColor3f(0, 1, 0);
    drawTriangle(t_point);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Triangle Rotation");

    gluOrtho2D(0, 400, 0, 400);

    glutDisplayFunc(display);
    glutMainLoop();
}
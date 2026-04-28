#include <GLUT/glut.h>
#include <math.h>

void drawLine(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void drawCircle(float cx, float cy, float r) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; i++) {
        float angle = 2.0f * 3.1416f * i / 100;
        float x = r * cos(angle);
        float y = r * sin(angle);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void drawEllipse(float cx, float cy, float rx, float ry) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; i++) {
        float angle = 2.0f * 3.1416f * i / 100;
        float x = rx * cos(angle);
        float y = ry * sin(angle);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // ===== AXES (ORIGIN SHOW) =====
    glColor3f(1.0, 1.0, 1.0);
    drawLine(-1.0, 0.0, 1.0, 0.0); // X-axis
    drawLine(0.0, -1.0, 0.0, 1.0); // Y-axis

    // ===== TOP LEFT: PARALLEL LINES =====
    glColor3f(1.0, 0.0, 0.0);
    drawLine(-0.9, 0.8, -0.2, 0.8);
    drawLine(-0.9, 0.6, -0.2, 0.6);

    // ===== TOP RIGHT: PERPENDICULAR LINES =====
    glColor3f(0.0, 1.0, 0.0);
    drawLine(0.3, 0.9, 0.9, 0.9); // horizontal
    drawLine(0.6, 0.5, 0.6, 1.0); // vertical
    
    // ===== BOTTOM LEFT: CIRCLE =====
    glColor3f(0.0, 0.0, 1.0);
    drawCircle(-0.6, -0.6, 0.2);

    // ===== BOTTOM RIGHT: ELLIPSE =====
    glColor3f(1.0, 0.0, 1.0);
    drawEllipse(0.6, -0.6, 0.25, 0.15);

    // ===== CENTER: CONCENTRIC CIRCLES =====
    glColor3f(1.0, 1.0, 0.0);
    drawCircle(0.0, 0.0, 0.1);
    drawCircle(0.0, 0.0, 0.2);
    drawCircle(0.0, 0.0, 0.3);

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Non-overlapping Graphics");

    init();
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
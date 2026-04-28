#include <GL/freeglut.h>
#include <math.h>

float a = 0.5;   // width
float b = 0.3;   // height
int segments = 100;

int winW = 600, winH = 600;

// Draw ellipse
void drawEllipse() {
    glBegin(GL_TRIANGLE_FAN);

    // center (red)
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(0.0, 0.0);

    // boundary (blue)
    glColor3f(0.0, 0.0, 1.0);

    for (int i = 0; i <= segments; i++) {
        float theta = 2.0f * 3.1416f * i / segments;
        float x = a * cos(theta);
        float y = b * sin(theta);
        glVertex2f(x, y);
    }

    glEnd();
}

// Bounding box (bonus)
void drawBoundingBox() {
    glColor3f(1.0, 1.0, 0.0);

    glBegin(GL_LINE_LOOP);
    glVertex2f(-a, -b);
    glVertex2f(a, -b);
    glVertex2f(a, b);
    glVertex2f(-a, b);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawEllipse();
    drawBoundingBox(); // optional

    glFlush();
}

// 🔥 Aspect Ratio Fix (IMPORTANT PART)
void reshape(int w, int h) {
    winW = w;
    winH = h;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspect = (float)w / h;

    if (aspect >= 1.0) {
        gluOrtho2D(-aspect, aspect, -1.0, 1.0);
    } else {
        gluOrtho2D(-1.0, 1.0, -1.0/aspect, 1.0/aspect);
    }

    glMatrixMode(GL_MODELVIEW);
}

// Keyboard controls
void keyboard(unsigned char key, int x, int y) {
    if (key == 'w') b += 0.05;   // increase height
    if (key == 's') b -= 0.05;

    if (key == 'd') a += 0.05;   // increase width
    if (key == 'a') a -= 0.05;

    if (a < 0.05) a = 0.05;
    if (b < 0.05) b = 0.05;

    glutPostRedisplay();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(winW, winH);
    glutCreateWindow("Adjustable Ellipse with Aspect Ratio");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape); // ⭐ important

    glutMainLoop();
    return 0;
}
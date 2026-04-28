#include <GL/freeglut.h>
#include <math.h>
float t = 0.0;
// Bezier function
float bezier(float p0, float p1, float p2, float p3, float u) {
    float oneMinusU = 1 - u;
    return oneMinusU*oneMinusU*oneMinusU*p0 +
           3*u*oneMinusU*oneMinusU*p1 +
           3*u*u*oneMinusU*p2 +
           u*u*u*p3;
}
// Draw one Bezier strip
void drawStrip(float y, float offset) {
    glBegin(GL_LINE_STRIP);
    for (float u = 0; u <= 1; u += 0.01) {
        float x = bezier(100, 200, 300, 400, u);
        float yy = bezier(y, y+offset, y-offset, y, u);
        glVertex2f(x, yy);
    }
    glEnd();
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Saffron
    glColor3f(1.0, 0.5, 0.0);
    for (float y = 250; y < 270; y += 2)
        drawStrip(y, 20 * sin(t));

    // White
    glColor3f(1, 1, 1);
    for (float y = 230; y < 250; y += 2)
        drawStrip(y, 20 * sin(t));

    // Green
    glColor3f(0, 1, 0);
    for (float y = 210; y < 230; y += 2)
        drawStrip(y, 20 * sin(t));

    glFlush();
}
void update(int value) {
    t += 0.1;  // animation speed
    glutPostRedisplay();
    glutTimerFunc(30, update, 0);
}
void init() {
    glClearColor(0, 0, 0, 1);
    gluOrtho2D(0, 500, 0, 500);
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Bezier Flag Animation");

    init();

    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);

    glutMainLoop();
}
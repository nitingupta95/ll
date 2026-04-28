#include <GL/freeglut.h>
float angle = 0;
float tx = -1.5;
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(tx, 0.0, -5.0);
    glScalef(1.0, 2.0, 1.0);
    glRotatef(angle, 0.0, 1.0, 0.0);
    glColor3f(0.0, 1.0, 1.0);
    glutWireCube(1.0);
    glutSwapBuffers();
}
void timer(int v) {
    angle += 1;
    tx += 0.01;
    if (tx > 1.5) tx = -1.5;
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}
void init() {
    glClearColor(0,0,0,1);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(60, 1, 1, 20);
    glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600,600);
    glutCreateWindow("3D Transformations");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}
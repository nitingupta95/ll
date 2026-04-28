#include <GL/freeglut.h>
#include <math.h>

// Camera position
float camX = 0, camY = 0, camZ = 5;

// Look direction
float lookX = 0, lookY = 0, lookZ = 0;

void drawCube() {
    glBegin(GL_QUADS);

    // Front (Red)
    glColor3f(1, 0, 0);
    glVertex3f(-1, -1, 1);
    glVertex3f(1, -1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(-1, 1, 1);

    // Back (Green)
    glColor3f(0, 1, 0);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, 1, -1);
    glVertex3f(1, 1, -1);
    glVertex3f(1, -1, -1);

    // Left (Blue)
    glColor3f(0, 0, 1);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, -1, 1);
    glVertex3f(-1, 1, 1);
    glVertex3f(-1, 1, -1);

    // Right (Yellow)
    glColor3f(1, 1, 0);
    glVertex3f(1, -1, -1);
    glVertex3f(1, 1, -1);
    glVertex3f(1, 1, 1);
    glVertex3f(1, -1, 1);

    // Top (Cyan)
    glColor3f(0, 1, 1);
    glVertex3f(-1, 1, -1);
    glVertex3f(-1, 1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(1, 1, -1);

    // Bottom (Magenta)
    glColor3f(1, 0, 1);
    glVertex3f(-1, -1, -1);
    glVertex3f(1, -1, -1);
    glVertex3f(1, -1, 1);
    glVertex3f(-1, -1, 1);

    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(camX, camY, camZ,
              lookX, lookY, lookZ,
              0, 1, 0);

    drawCube();

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    float speed = 0.2;

    // Direction vector
    float dirX = lookX - camX;
    float dirY = lookY - camY;
    float dirZ = lookZ - camZ;

    float len = sqrt(dirX*dirX + dirY*dirY + dirZ*dirZ);
    dirX /= len; dirY /= len; dirZ /= len;

    // Right vector
    float rightX = dirZ;
    float rightZ = -dirX;

    if (key == 'w') {
        camX += dirX * speed;
        camZ += dirZ * speed;
        lookX += dirX * speed;
        lookZ += dirZ * speed;
    }
    if (key == 's') {
        camX -= dirX * speed;
        camZ -= dirZ * speed;
        lookX -= dirX * speed;
        lookZ -= dirZ * speed;
    }
    if (key == 'a') {
        camX -= rightX * speed;
        camZ -= rightZ * speed;
        lookX -= rightX * speed;
        lookZ -= rightZ * speed;
    }
    if (key == 'd') {
        camX += rightX * speed;
        camZ += rightZ * speed;
        lookX += rightX * speed;
        lookZ += rightZ * speed;
    }
    if (key == 'q') {
        camY += speed;
        lookY += speed;
    }
    if (key == 'e') {
        camY -= speed;
        lookY -= speed;
    }

    glutPostRedisplay();
}

void init() {
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, 1, 100);

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Color Cube with Camera");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
}
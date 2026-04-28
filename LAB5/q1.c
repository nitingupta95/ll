#include <GL/freeglut.h>
#include <math.h>
float square[4][2] = {
    {-0.2, -0.2},
    { 0.2, -0.2},
    { 0.2,  0.2},
    {-0.2,  0.2}
};
float transformed[4][2];
void applyTransform() {
    float tx = 0.4, ty = 0.3;     // translation
    float sx = 1.5, sy = 0.5;     // scaling
    float angle = 45 * 3.1416 / 180; // rotation
    float shx = 0.5, shy = 0.0;   // shearing
    for(int i = 0; i < 4; i++) {
        float x = square[i][0];
        float y = square[i][1];
        x = x * sx;
        y = y * sy;
        float xr = x*cos(angle) - y*sin(angle);
        float yr = x*sin(angle) + y*cos(angle);
        xr = xr + shx * yr;
        yr = yr + shy * xr;
        xr += tx;
        yr += ty;
        transformed[i][0] = xr;
        transformed[i][1] = yr;
    }
}
void drawSquare(float arr[4][2]) {
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < 4; i++) {
        glVertex2f(arr[i][0], arr[i][1]);
    }
    glEnd();
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,1,1);
    drawSquare(square);
    applyTransform();
    glColor3f(1,0,0);
    drawSquare(transformed);
    glFlush();
}
void init() {
    glClearColor(0,0,0,1);
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("2D Transformations");
    glutInitWindowSize(600,600);
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
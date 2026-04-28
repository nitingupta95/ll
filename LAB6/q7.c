#include <GL/freeglut.h>
#include <stdio.h>

#define MAX 50

typedef struct {
    float x, y;
} Point;

Point input[MAX], original[MAX];
int n;

float xmin, ymin, xmax, ymax;

// Inside test
int inside(Point p, int edge) {
    switch(edge) {
        case 0: return p.x >= xmin; // left
        case 1: return p.x <= xmax; // right
        case 2: return p.y >= ymin; // bottom
        case 3: return p.y <= ymax; // top
    }
    return 0;
}

// Intersection
Point intersect(Point p1, Point p2, int edge) {
    Point p;
    float m = 0;

    if (p2.x != p1.x)
        m = (p2.y - p1.y) / (p2.x - p1.x);

    switch(edge) {
        case 0: // left
            p.x = xmin;
            p.y = p1.y + m * (xmin - p1.x);
            break;

        case 1: // right
            p.x = xmax;
            p.y = p1.y + m * (xmax - p1.x);
            break;

        case 2: // bottom
            p.y = ymin;
            p.x = p1.x + (ymin - p1.y) / m;
            break;

        case 3: // top
            p.y = ymax;
            p.x = p1.x + (ymax - p1.y) / m;
            break;
    }
    return p;
}

// Clipping step
void clip(int edge) {
    Point temp[MAX];
    int k = 0;

    for (int i = 0; i < n; i++) {
        Point curr = input[i];
        Point prev = input[(i + n - 1) % n];

        int curr_in = inside(curr, edge);
        int prev_in = inside(prev, edge);

        if (curr_in) {
            if (!prev_in)
                temp[k++] = intersect(prev, curr, edge);
            temp[k++] = curr;
        }
        else if (prev_in) {
            temp[k++] = intersect(prev, curr, edge);
        }
    }

    n = k;
    for (int i = 0; i < n; i++)
        input[i] = temp[i];
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw window
    glColor3f(0, 1, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();

    // Draw original polygon
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < n; i++)
        glVertex2f(original[i].x, original[i].y);
    glEnd();

    // Perform clipping
    clip(0);
    clip(1);
    clip(2);
    clip(3);

    // Draw clipped polygon
    glColor3f(0, 0, 1);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < n; i++)
        glVertex2f(input[i].x, input[i].y);
    glEnd();

    glFlush();
}

void init() {
    glClearColor(0, 0, 0, 1);
    gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char** argv) {

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter vertex %d (x y): ", i + 1);
        scanf("%f %f", &input[i].x, &input[i].y);
        original[i] = input[i];
    }

    printf("Enter xmin ymin xmax ymax: ");
    scanf("%f %f %f %f", &xmin, &ymin, &xmax, &ymax);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Polygon Clipping - User Input");

    init();
    glutDisplayFunc(display);

    glutMainLoop();
}
#include <iostream>

#include "src/Sphere.h"
#include "src/Cube.h"
#include "src/Ray.h"
#include "src/Transformation.h"
#include "src/Collision.h"
#include "src/Math/Vec4.h"

#include "GL/glut.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define W ((double)WINDOW_WIDTH/2)
#define H ((double)WINDOW_HEIGHT/2)
#define N 300 // Distance to near plane

void openGLInit();
void drawDot(GLint x, GLint y);
void renderer();

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Ray Tracer - Gaetan Blankers");
    glutDisplayFunc(renderer);
    openGLInit();
    glutMainLoop();

    return 0;
}

void openGLInit(){
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-W, W, -H,H);
}

void drawDot(GLint x, GLint y){
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void renderer(){

    // Generate sphere
    Transformation t;
    t.addTranslation(800, 0, 0);
    t.addScaling(200, 200, 200);
//    Sphere testSphere(t, 1, 1, 0);
//    Transformation t2;
//    t2.addTranslation(600, 200,-250);
//    t2.addScaling(200, 200, 200);
//    Sphere testSphere2(t2, 0, 0, 1);
//    Transformation t3;
//    t3.addTranslation(600, 100,100);
//    t3.addScaling(40, 40, 40);
//    Sphere testSphere3(t3, 0, 0, 1);

    Cube testCube(t, 0, 1, 0);

    int numObjects = 1;
    Shape *scene[numObjects];
    scene[0] = &testCube;
//    scene[0] = &testSphere;
//    scene[1] = &testSphere2;
//    scene[2] = &testSphere3;

    Ray eye(Vec4(0, 0, 0, 1), Vec4(1, 0, 0, 0),
            Vec4(0, 1, 0, 0));
    Collision c;

    float previousHit;

    glClear(GL_COLOR_BUFFER_BIT);
    for(int i = -W; i<W; i++){
        for(int j = -H; j<H; j++){
            previousHit = MAXFLOAT;
            for(int object = 0; object < numObjects; object++){
                eye.setPixel(N, i, j);
                c = scene[object]->checkCollision(eye);
                if(previousHit > c.getT() && c.getT() > 0){
                    glColor3d(c.getR(), c.getG(), c.getB());
                    drawDot(i, j);
                    previousHit = (float)c.getT();
                }
            }
        }
    }
    glFlush();
}
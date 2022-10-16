#include <iostream>

#include "src/Sphere.h"
#include "src/Ray.h"
#include "src/Transformation.h"
#include "src/Collision.h"
#include "src/settings.h"
#include "src/Math/Matrix4.h"
#include "src/Math/Vec4.h"

#include "GL/glut.h"

#include <cmath>

#define H 1000
#define W 1000
#define N 10

void openGLInit(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Ray Tracer");

    // Color to be used when the buffers are cleared
    glClearColor(0.0,0.0,0.0,1.0);

    //set the diameter of rasterized points
    glPointSize(1.0);

    glDisable(GL_LIGHTING);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-W, W, -H, H);
}

int main(int argc, char** argv) {
//    int numObjects = 2;
//    Shape *scene[numObjects];
//    scene[0] = &newSphere;
//    scene[1] = &newSphere2;


    // Generate sphere
    Transformation t;
    t.addTranslation(50, 0, 0);
    Sphere testSphere(t, 1, 1, 0);

    int numObjects = 1;
    Shape *scene[numObjects];
    scene[0] = &testSphere;

    openGLInit(argc, argv);

    glColor3f(1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);

    Ray eye(Vec4(0, 0, 0, 1), Vec4());
    Collision c;

    for(int i = -W; i<W; i++){
        for(int j = -H; j<H; j++){
            for(int object = 0; object < numObjects; object++){
                eye.setDirectionVector(Vec4(1, i, j, 0));
                c = scene[object]->checkCollision(eye);

                if(c.getT()>0){
                    glColor3d(scene[object]->getR(), scene[object]->getG(),scene[object]->getB());
                    glVertex2i(i, j);
                }
            }
        }
    }

    glFlush();
    glEnd();
    glutMainLoop();

    return 0;
}

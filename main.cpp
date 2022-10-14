#include <iostream>

//#include "src/Sphere.h"
//#include "src/Ray.h"
//#include "src/Transformation.h"
//#include "src/Collision.h"
#include "src/settings.h"
#include "src/Math/Matrix4.h"
#include "src/Math/Vec4.h"

#include "GL/glut.h"

#include <cmath>

#define H 200
#define W 200
#define N 10

void openGLInit(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(0,0);

    glutCreateWindow("Test");

    // Color to be used when the buffers are cleared
    glClearColor(1.0,1.0,1.0,1.0);

    //set the diameter of rasterized points
    glPointSize(1.0);

    glDisable(GL_LIGHTING);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(-W, W, -H, H);
}

int main(int argc, char** argv) {

//    trans t{};
//    t.translation = Vec4(0, 0, 0, 0);
//    t.scale = Vec4(10, 10, 10, 0);
//
//    Transformation transformationSphere(t);
//
//    Sphere newSphere(transformationSphere);
//    trans t2{};
//    t2.translation = Vec4(0, 500, 500);
//    t2.scale = Vec4(1000, 1000, 1000);
//
//    Transformation transformationSphere2(t2);
//
//    Sphere newSphere2(transformationSphere);
//
//    Ray eyeRay(Vec4(-5, 0, 0), Vec4(0, 0, 0));
//
//    openGLInit(argc, argv);
//
//    int numObjects = 2;
//    Shape *scene[numObjects];
//    scene[0] = &newSphere;
//    scene[1] = &newSphere2;
//
//    // Set the color for the pixel to draw
//    glColor3f(1.0,0.0,0.0);
//
//    glClear(GL_COLOR_BUFFER_BIT);
//    glBegin(GL_POINTS);
//
//    for(int objectNr=0; objectNr<numObjects; objectNr++){
//        if(objectNr==1){
//            // Set the color for the pixel to draw
//            glColor3f(0.0,1.0,0.0);
//        }
//        for(int i=0; i<WINDOW_WIDTH; i++){
//            for(int j=0; j<WINDOW_HEIGHT; j++){
//                eyeRay.setDirectionVector(Vec4(-N, W * ((2 * (double)j) / WINDOW_HEIGHT) - 1, H * ((2 * (double)i) / WINDOW_WIDTH) - 1));
//                Collision c = scene[objectNr]->checkCollision(eyeRay);
//                if(c.getT()>0){
//                    int pixelX = (int)(-H + H*((2*(double)i)/WINDOW_WIDTH));
//                    int pixelY = (int)(-W + W*((2*(double)j)/WINDOW_HEIGHT));
//                    glVertex2i(pixelX, pixelY);
//                }
//            }
//        }
//    }
//
//
//    glEnd();
//    glFlush();
//
//
//    glutMainLoop();


    return 0;
}

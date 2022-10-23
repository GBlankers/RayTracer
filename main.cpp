#include <iostream>

#include "src/Objects/Sphere.h"
#include "src/Objects/Cube.h"
#include "src/Objects/Plane.h"
#include "src/Ray.h"
#include "src/Transformation.h"
#include "src/Collision.h"
#include "src/Math/Vec4.h"

#include "GL/glut.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define W ((double)WINDOW_WIDTH)
#define H ((double)WINDOW_HEIGHT)
#define N 1800 // Distance to near plane

#define DEG_TO_RADIANS(X) (X*M_PI/180)

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

    Transformation t1;
    t1.addScaling(400, 400, 400);
    t1.addTranslation(2000, -1000,-1000);
    Sphere testSphere(t1, 0, 0, 1);

    Transformation t3;
    t3.addScaling(400, 400, 400);
    t3.addTranslation(2000, -500,-500);
    Sphere testSphere3(t3, 0, 1, 0);

    Transformation t4;
    t4.addScaling(400, 400, 400);
    t4.addTranslation(2000, 0,0);
    Sphere testSphere4(t4, 1, 0, 0);

    Transformation t5;
    t5.addScaling(400, 400, 400);
    t5.addTranslation(2000, 500,500);
    Sphere testSphere5(t5, 0, 1, 0);

    Transformation t6;
    t6.addScaling(400, 400, 400);
    t6.addTranslation(2000, 1000,1000);
    Sphere testSphere6(t6, 0, 0, 1);


    Transformation tCube;
    tCube.addScaling(400, 400, 400);
    tCube.addRotationY(DEG_TO_RADIANS(-30));
    tCube.addRotationX(DEG_TO_RADIANS(30));
    tCube.addTranslation(2000, 800, -1200);
    Cube testCube(tCube, 1, 1, 0);

    Transformation tCube2;
    tCube2.addScaling(400, 400, 400);
    tCube2.addRotationY(DEG_TO_RADIANS(-30));
    tCube2.addRotationX(DEG_TO_RADIANS(30));
    tCube2.addTranslation(2000, -800, 1200);
    Cube testCube2(tCube2, 0, 1, 1);

    Transformation tPlane;
    tPlane.addTranslation(0, -2000, 0);
    Plane testPlane(tPlane, 0.5, 0.5, 0.5);


    int numObjects = 8;
    Shape *scene[numObjects];
    scene[0] = &testSphere;
    scene[1] = &testSphere3;
    scene[2] = &testSphere4;
    scene[3] = &testSphere5;
    scene[4] = &testSphere6;
    scene[5] = &testCube;
    scene[6] = &testCube2;
    scene[7] = &testPlane;

    Ray eye(Vec4(-N, 0, 0, 1), Vec4(1, 0, 0, 0),
            Vec4(0, 1, 0, 0));
    LightSource light({0,700,0,1}, {1200,-400,0,0});
    Collision c;

    float previousHit;
    double progress = 0;
    glClear(GL_COLOR_BUFFER_BIT);

    for(int i = -W; i<W; i++){
        for(int j = -H; j<H; j++){
            previousHit = MAXFLOAT;
            for(int object = 0; object < numObjects; object++){
                eye.setPixel(N, i, j);
                c = scene[object]->checkCollision(eye, light);
                if(previousHit > c.getT() && c.getT() > 0){
                    glColor3d(c.getR(), c.getG(), c.getB());
                    drawDot(i, j);
                    previousHit = (float)c.getT();
                }
            }
        }
        //std::cout << "Progress: " << ((i+W)*100/(2*W)) << "%" << std::endl;
        glFlush();
    }
}
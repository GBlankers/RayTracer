#include <iostream>

#include "src/Sphere.h"
#include "src/Ray.h"
#include "src/Transformation.h"
#include "src/Collision.h"
#include "src/Math/Vec4.h"

#include "GL/glut.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define W ((double)WINDOW_WIDTH/2)
#define H ((double)WINDOW_HEIGHT/2)
#define N 10 // Distance to near plane

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
    t.addTranslation(15, 100, 100);
    t.addScaling(10, 10, 10);
    Sphere testSphere(t, 1, 1, 0);

    int numObjects = 1;
    Shape *scene[numObjects];
    scene[0] = &testSphere;

    Ray eye(Vec4(-N, 0, 0, 1), Vec4(1, 0, 0, 0),
            Vec4(0, 1, 0, 0));
    Collision c;
    glClear(GL_COLOR_BUFFER_BIT);
    for(int i = -W; i<W; i++){
        for(int j = -H; j<H; j++){
            for(int object = 0; object < numObjects; object++){
                eye.setPixel(N, i, j);
                c = scene[object]->checkCollision(eye);

                if(c.getT()>0){
                    std::cout << "hit" << std::endl;
                    std::cout << "x: " << c.getCollisionPoint().getX() << " y: " << c.getCollisionPoint().getY() <<
                    " z: " << c.getCollisionPoint().getZ() << std::endl;
                    std::cout << "pixel x: " << i << " pixel y: " << j << std::endl;

                    glColor3d(scene[object]->getR(), scene[object]->getG(),scene[object]->getB());
                    drawDot(i, j);
                }
            }
        }
    }
    glFlush();
}
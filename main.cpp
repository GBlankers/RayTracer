#include <iostream>
#include <chrono>
#include <random>

#include "src/Objects/Sphere.h"
#include "src/Ray.h"
#include "src/Collision.h"
#include "src/Math/Vec4.h"

#include "GL/glut.h"
#include "src/Scene.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define W ((double)WINDOW_WIDTH)
#define H ((double)WINDOW_HEIGHT)
#define N 1800 // Distance to near plane

void openGLInit();
void drawDot(GLint x, GLint y);
void renderer();
double randomDouble();

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

double randomDouble(){
    static std::uniform_real_distribution<double> distribution(-1.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

void renderer(){

    Scene world;

    Ray eye(Vec4(-N, 0, 0, 1), Vec4(1, 0, 0, 0),
            Vec4(0, 1, 0, 0));
    LightSource light({0,700,0,1}, {1200,-400,0,0});
    Collision c;

    float previousHit;
    Vec4 color{};
    glClear(GL_COLOR_BUFFER_BIT);
    Scene::iterator shapePointer;

    auto start = std::chrono::high_resolution_clock::now();
    for(int i = -W; i<W; i++){
        for(int j = -H; j<H; j++){
            previousHit = MAXFLOAT;
            color.reset();
            eye.setPixel(N, i, j);
            for(shapePointer = world.begin(); shapePointer != world.end(); shapePointer++){
                c = shapePointer->get()->checkCollision(eye, light);
                if(previousHit > c.getT() && c.getT() > 0){
                    previousHit = (float)c.getT();
                    color = Vec4(c.getR(), c.getG(), c.getB(), 0);
                }
            }
            glColor3d(color.getX(), color.getY(), color.getZ());
            drawDot(i, j);
        }
        glFlush();
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    std::cout << "Time elapsed during rendering: " << duration.count() << " s" << std::endl;
}
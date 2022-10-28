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
#define ANTI_ALIAS_SAMPLING 3

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
    world.fillScene3();
    auto worldObjects(world.getObjectVector());
    auto worldLighting(world.getLightVector());

    Ray eye(Vec4(-N, 0, 0, 1), Vec4(1, 0, 0, 0),
            Vec4(0, 1, 0, 0));
    Collision c;

    float previousHit;
    Vec4 color{}, tempColor{};
    glClear(GL_COLOR_BUFFER_BIT);

    auto start = std::chrono::high_resolution_clock::now();
    for(int i = -W; i<W; i++){
        for(int j = -H; j<H; j++){
            color.reset();
            for(int alias = 0; alias<ANTI_ALIAS_SAMPLING; alias++){
                previousHit = MAXFLOAT;
                tempColor.reset();
                eye.setPixel(N, i+randomDouble(), j+randomDouble());
                for(auto & worldObject : worldObjects){
                    c = worldObject->checkCollision(eye, worldLighting, worldObjects);
                    if(previousHit > c.getT() && c.getT() > 0){
                        previousHit = (float)c.getT();
                        tempColor = Vec4(c.getR(), c.getG(), c.getB(), 0);
                    }
                }
                color = color + tempColor;
            }
            color = color*(1.0/ANTI_ALIAS_SAMPLING);
            glColor3d(color.getX(), color.getY(), color.getZ());
            drawDot(i, j);
        }
        glFlush();
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    std::cout << "Time elapsed during rendering: " << duration.count() << " s" << std::endl;
}

// TODO: fix cone ground plane
// TODO: how to do shadows if the scene can't be given as an argument to the shape class?

// TODO: materials
// TODO: uv-mapping
// TODO: extra: progressive rendering, movable camera, dynamically change the scene using ImGUI
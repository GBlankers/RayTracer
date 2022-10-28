#include <iostream>
#include <chrono>
#include <random>

#include "src/Objects/Sphere.h"
#include "src/Ray.h"
#include "src/Collision.h"
#include "src/Math/Vec4.h"

#include "GL/glut.h"
#include "src/Scene.h"

// Window constants
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
// Virtual screen coordinates
#define W ((double)WINDOW_WIDTH)
#define H ((double)WINDOW_HEIGHT)
// Anti alias samples
#define ANTI_ALIAS_SAMPLING 3

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
    world.fillScene();
    auto worldObjects(world.getObjectVector());

    Ray eye(Vec4(-N, 0, 0, 1), Vec4(1, 0, 0, 0),
            Vec4(0, 1, 0, 0));
    LightSource light({0,700,-1000,1}, {2000,-400,1000,0});
    Collision c;

    float previousHit;
    Vec4 color{}, tempColor{};
    glClear(GL_COLOR_BUFFER_BIT);

    // For timing and testing purpose
    auto start = std::chrono::high_resolution_clock::now();
    // Go over all the pixels in the near screen
    for(int i = -W; i<W; i++){
        for(int j = -H; j<H; j++){
            // Reset the color for each pixel then we can average for the anti-aliasing
            color.reset();
            // Shoot a couple rays in almost the same direction
            for(int alias = 0; alias<ANTI_ALIAS_SAMPLING; alias++){
                previousHit = MAXFLOAT;
                tempColor.reset();
                eye.setPixel(N, i+randomDouble(), j+randomDouble());
                // Go over all the objects
                for(auto & worldObject : worldObjects){
                    // For every object, check if the ray hits
                    c = worldObject->checkCollision(eye, light);
                    // the t (used in the ray equation y = a + x*t) must be larger than 0. Otherwise, the ray shoots
                    // backwards. T must be smaller than the previous t to ensure that the closest object hits.
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
// TODO: dots on cube
// TODO: how to do shadows if the scene can't be given as an argument to the shape class?

// TODO: materials
// TODO: uv-mapping
// TODO: extra: progressive rendering, movable camera, dynamically change the scene using ImGUI
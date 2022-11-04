#include <iostream>
#include <chrono>
#include <random>

#include "src/Ray.h"
#include "src/Collision.h"
#include "src/Math/Vec4.h"
#include "src/Scene.h"
#include "src/Camera.h"

#include "GL/glut.h"

// Window constants
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
// Virtual screen coordinates
#define W ((double)WINDOW_WIDTH)
#define H ((double)WINDOW_HEIGHT)
// Anti alias samples
#define ANTI_ALIAS_SAMPLING 1

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
    // Define a scene
    Scene world;
    world.fillScene();
    auto worldObjects(world.getObjectVector());
    auto worldLighting(world.getLightVector());

    // initialise the camera
    Camera camera(2*W, 10, {2000, 0, 0, 1},
                  {0, 200, 0, 1});

    // Pre defined variables
    Collision c;
    Ray shotRay{};
    float previousHit;
    double intensity, maxIntensity;
    bool clearPathToLight;
    Vec4 color{}, tempColor{};

    // Clear the screen
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
                shotRay = camera.getRayFromPixel(i+randomDouble(), j+randomDouble());
                // Go over all the objects
                for(auto & worldObject : worldObjects){
                    // For every object, check if the ray hits
                    c = worldObject->checkCollision(shotRay);
                    // the t (used in the ray equation y = a + x*t) must be larger than 0. Otherwise, the ray shoots
                    // backwards. T must be smaller than the previous t to ensure that the closest object hits.
                    if(previousHit > c.getT() && c.getT() > 0){
                        previousHit = (float)c.getT();

                        // Add ambient light
                        intensity = worldObject->ambientIntensity();
                        // Check if the object is in the shadow

                        // Go over all the light sources
                        for(const auto& light: worldLighting){
                            // Assume there is a clear path to the light source
                            clearPathToLight = true;
                            // Go over all the objects in the world
                            for(const auto& obj: worldObjects){
                                // Do not check the for an intersection with itself
                                // + check if the light is blocked by other objects
                                if(obj.get() != worldObject.get() and obj->checkHit(Ray{c.getCollisionPoint(),
                                                                                        light->getPosition() - c.getCollisionPoint()})) {
                                    // There is no clear path to the light -> there will be shadows
                                    clearPathToLight = false;
                                }
                            }
                            // If there is a clear path -> calculate the diffuse and specular components
                            if(clearPathToLight){
                                // Inverse transform the light source
                                Matrix4 inverseTransform = worldObject->getT().getInverse();
                                light->transform(inverseTransform);
                                // Calculate the diffuse component
                                intensity += worldObject->getDiffuse()*light->calculateDiffuse(
                                        worldObject->calculateNormal(inverseTransform * c.getCollisionPoint()),
                                        inverseTransform * c.getCollisionPoint())*light->getIntensity();
                                // calculate the specular component
                                intensity += worldObject->getSpecular()*light->calculateSpecular(
                                        Vec4::normalize(shotRay.getDirectionVector())*-1, c.getCollisionPoint())
                                                *light->getIntensity();
                            }
                        }
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
// TODO: reflection
// TODO: refraction
// TODO: materials
// TODO: uv-mapping
// TODO: EXTRA: progressive rendering, movable camera, dynamically change the scene using ImGUI
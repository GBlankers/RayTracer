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
#define ANTI_ALIAS_SAMPLING 2

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
    world.fillScene("include/general.json");
    //world.fillScene3();
    auto worldObjects(world.getObjectVector());
    auto worldLighting(world.getLightVector());

    // initialise the camera
    Camera camera(2*W, 10, {2000, 0, 0, 1},
                  {0, 100, 0, 1});

    // Pre defined variables
    Collision c;
    Ray shotRay{};
    float previousHit;
    double ambient, diffuse, specular;
    bool clearPathToLight;
    Vec4 color{}, tempColor{}, normal{};

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
                        // Get the ambient intensity
                        ambient = worldObject->getAmbient();
                        // Check if in shadow, otherwise do not calculate the diffuse and specular components
                        for(const auto& light: worldLighting){
                            // Assume there is a clear path to the light source
                            clearPathToLight = true;
                            // Calculate the ray between the hit point and the light source
                            Ray r(c.getCollisionPoint(), light->getPosition()-c.getCollisionPoint());
                            // Check all the objects in the world
                            for(const auto & obj: worldObjects){
                                // If the object is not the current object and the ray hits than there is not clear path
                                if(obj != worldObject and obj->checkHit(r)){
                                    clearPathToLight = false;
                                }
                            }
                            // Calculate diffuse and spectral components if there is a clear path to the light source
                            if(clearPathToLight){
                                normal = worldObject->calculateNormal(c.getCollisionPoint());
                                diffuse = light->calculateDiffuse(normal, c.getCollisionPoint());
                                specular = light->calculateSpecular(normal, shotRay.getDirectionVector(), c.getCollisionPoint());
                                tempColor = worldObject->calculateDiffuseSpecularColor(diffuse, specular, light->getColor(), c);
                            }
                        }

                        // Ambient coefficient * color of object
                        // + diffuse intensity * diffuse coefficient * color of object * color of light
                        // + specular intensity * specular coefficient * color of object * color of light

                        tempColor = Vec4::clamp(tempColor + c.getColor()*ambient);
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

// TODO: reflection
// TODO: refraction
// TODO: materials
// TODO: uv-mapping
// TODO: EXTRA: progressive rendering, movable camera, dynamically change the scene using ImGUI
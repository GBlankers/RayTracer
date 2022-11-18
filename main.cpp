#include <iostream>
#include <chrono>
#include <thread>
#include <pthread.h>

#include "src/Ray.h"
#include "src/Collision.h"
#include "src/Math/Vec4.h"
#include "src/Scene.h"
#include "src/settings.h"

#include "src/Math/Utils.h"

#include "GL/glut.h"

void openGLInit();
void drawDot(GLint x, GLint y);
void renderer();

Vec4 reflect(Ray incomingRay, Collision collisionPoint, int reflectionsToGo, const Scene& scene);
Vec4 lighting(const std::shared_ptr<Shape>& shape, Collision c, Ray incoming, const Scene& scene);
void goOverPixels(const Scene& s, std::vector<Vec4>& pixelList, int begin, int end);

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

Vec4 lighting(const std::shared_ptr<Shape>& shape, Collision c, Ray incoming, const Scene& scene){
    double diffuse, specular;
    Vec4 totalLight(0, 0, 0, 0), tempColor(0, 0, 0, 0);
    bool clearPathToLight;

    // Get the ambient intensity
    double ambient = shape->getAmbient();
    // Check if in shadow, otherwise do not calculate the diffuse and specular components
    for(const auto& l: scene.getLightVector()){
        // Assume there is a clear path to the light source
        clearPathToLight = true;
        // Calculate the ray between the hit point and the light source
        Ray r(c.getCollisionPoint(), l->getPosition()-c.getCollisionPoint());
        // Check all the objects in the world
        for(const auto & obj: scene.getObjectVector()){
            // If the object is not the current object and the ray hits than there is not clear path
            double t;
            if(obj != shape and obj->checkHit(r, t)){
                // Only a hit when there is an object between a light source and another object
                if(t<=1 and t>=0)
                    clearPathToLight = false;
            }
        }
        // Calculate diffuse and spectral components if there is a clear path to the light source
        if(clearPathToLight){
            diffuse = l->calculateDiffuse(c.getNormal(), c.getCollisionPoint());
            specular = l->calculateSpecular(c.getNormal(), incoming.getDirectionVector(), c.getCollisionPoint());
            tempColor = shape->calculateDiffuseSpecularColor(diffuse, specular, l->getColor(), c);
        }
        totalLight = totalLight + c.getColor() * ambient + tempColor;
    }
    return totalLight;
}

Vec4 reflect(Ray incomingRay, Collision collisionPoint, int reflectionsToGo, const Scene& scene){
    // Max number of reflections reached
    if(reflectionsToGo == 0){
        return {0, 0, 0, 0};
    }

    // calculate the reflected ray direction
    Vec4 rayDirection = Vec4::normalize(incomingRay.getDirectionVector() + collisionPoint.getNormal() *
                            (-2)*Vec4::dot(collisionPoint.getNormal(), incomingRay.getDirectionVector()));
    // create the ray, starts at t=0.1 to stop reflections with the object itself
    Ray reflectedRay(collisionPoint.getCollisionPoint()+ rayDirection*0.1,rayDirection);

    // Check all the world objects for a collision
    Collision c, closestC;
    std::shared_ptr<Shape> lastObjectHit;
    double previousHit = MAXFLOAT;
    for(auto & object : scene.getObjectVector()) {
        c = object->checkCollision(reflectedRay);
        if (previousHit > c.getT() && c.getT() > 0) {
            previousHit = (float) c.getT();
            closestC = c;
            lastObjectHit = object;
        }
    }

    if(previousHit == MAXFLOAT){
        return scene.getSkyColor(rayDirection);
    }

    // Return color of the current hit + further reflections
    return lighting(lastObjectHit, closestC, reflectedRay, scene) + reflect(reflectedRay, closestC, reflectionsToGo-1, scene)*lastObjectHit->getReflectivity();
}

void goOverPixels(const Scene& s, std::vector<Vec4>& pixelList, int begin, int end){
    auto camera(s.getCamera());

    // Pre defined variables
    Collision c, lastCollision;
    Ray shotRay{};
    float previousHit;
    Vec4 color{}, reflectedColor{}, lightColor{};
    std::shared_ptr<Shape> lastObjectHit;

    // Go over all the pixels in the near screen
    for(int i = begin; i<end; i++){
        for(int j = -H; j<H; j++){
            // Reset the color for each pixel then we can average for the anti-aliasing
            color.reset();
            // Shoot a couple rays in almost the same direction
            for(int alias = 0; alias<ANTI_ALIAS_SAMPLING; alias++){
                previousHit = MAXFLOAT;
                shotRay = camera.getRayFromPixel(i+randomDouble(), j+randomDouble());
                // Go over all the objects
                for(auto & worldObject : s.getObjectVector()){
                    // For every object, check if the ray hits
                    c = worldObject->checkCollision(shotRay);
                    // the t (used in the ray equation y = a + x*t) must be larger than 0. Otherwise, the ray shoots
                    // backwards. T must be smaller than the previous t to ensure that the closest object hits.
                    if(previousHit > c.getT() && c.getT() > 0){
                        previousHit = (float)c.getT();
                        lastObjectHit = worldObject;
                        lastCollision = c;
                    }
                }

                if(previousHit != MAXFLOAT){
                    // LIGHTING
                    lightColor = lighting(lastObjectHit, lastCollision, shotRay, s);
                    // REFLECTIONS
                    reflectedColor = reflect(shotRay, lastCollision, REFLECTIONS, s);
                    // Cumulate color -> anti alias;
                    color = color + Vec4::clamp(lightColor + reflectedColor * lastObjectHit->getReflectivity());
                } else {
                    color = color + s.getSkyColor(shotRay.getDirectionVector());
                }
            }
            color = color*(1.0/ANTI_ALIAS_SAMPLING);

            pixelList.push_back(color);
        }
    }
}

void renderer(){
    // Define a scene
    Scene world;
    world.fillScene("include/general.json");

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    auto start = std::chrono::high_resolution_clock::now();

    std::vector<Vec4> pixelList1;
    std::vector<Vec4> pixelList2;
    std::vector<Vec4> pixelList3;
    std::vector<Vec4> pixelList4;

    std::thread firstQuarter(goOverPixels, world, std::ref(pixelList1), -W, -W/2);
    std::thread secondQuarter(goOverPixels, world, std::ref(pixelList2), -W/2, 0);
    std::thread thirdQuarter(goOverPixels, world, std::ref(pixelList3), 0, W/2);
    std::thread finalQuarter(goOverPixels, world,std::ref(pixelList4), W/2, W);

    firstQuarter.join();
    for(int i = 0; i<W/2; i++){
        for(int j = 0; j<2*H; j++){
            Vec4 color = pixelList1.at(j+i*(2*H));
            glColor3d(color.getX(), color.getY(), color.getZ());
            drawDot(-W+i, -H+j);
        }
        glFlush();
    }
    secondQuarter.join();
    for(int i = 0; i<W/2; i++){
        for(int j = 0; j<2*H; j++){
            Vec4 color = pixelList2.at(j+i*(2*H));
            glColor3d(color.getX(), color.getY(), color.getZ());
            drawDot((-W/2)+i, -H+j);
        }
        glFlush();
    }
    thirdQuarter.join();
    for(int i = 0; i<W/2; i++){
        for(int j = 0; j<2*H; j++){
            Vec4 color = pixelList3.at(j+i*(2*H));
            glColor3d(color.getX(), color.getY(), color.getZ());
            drawDot(i, -H+j);
        }
        glFlush();
    }
    finalQuarter.join();
    for(int i = 0; i<W/2; i++){
        for(int j = 0; j<2*H; j++){
            Vec4 color = pixelList4.at(j+i*(2*H));
            glColor3d(color.getX(), color.getY(), color.getZ());
            drawDot((W/2)+i, -H+j);
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
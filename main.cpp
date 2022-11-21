#include <iostream>
#include <chrono>
#include <thread>

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

Vec4 lighting(const std::shared_ptr<Shape>& shape, Collision c, Ray incoming, const Scene& scene);
Vec4 reflect(Ray incomingRay, Collision collisionPoint, int reflectionsToGo, const Scene& scene);
Vec4 refract(const std::shared_ptr<Shape>& shape, Collision c, Ray incoming, const Scene& scene);
Vec4 objectColorHit(const std::shared_ptr<Shape>& shape, Collision c, Ray incoming, const Scene& scene);

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
    double diffuse, specular, t;
    Vec4 totalLight(0, 0, 0, 0), tempColor(0, 0, 0, 0), startPoint{};
    double pathToLight;
    Ray r{};
    // Get the ambient intensity
    double ambient = shape->getAmbient();
    // Check if in shadow, otherwise do not calculate the diffuse and specular components
    for(const auto& l: scene.getLightVector()){
        // Assume there is a clear path to the light source
        pathToLight = 1;
        // Calculate the start point a little in front of the object that was hit in order to not collide with itself
        startPoint = c.getCollisionPoint()+Vec4::normalize(l->getPosition()-c.getCollisionPoint())*0.1;
        // Calculate the ray between the hit point and the light source
        r = Ray(startPoint, l->getPosition()-c.getCollisionPoint());
        // Check all the objects in the world
        for(const auto & obj: scene.getObjectVector()){
            // If the object is not the current object and the ray hits than there is not clear path
            if(obj->checkHit(r, t)){
                // Only a hit when there is an object between a light source and another object
                if(t<=1 and t>=0)
                    pathToLight *= obj->getTransparency();
            }
        }
        // Calculate diffuse and spectral components if there is a clear path to the light source
        if(pathToLight>0){
            diffuse = l->calculateDiffuse(c.getNormal(), c.getCollisionPoint());
            specular = l->calculateSpecular(c.getNormal(), incoming.getDirectionVector(), c.getCollisionPoint());
            tempColor = shape->calculateDiffuseSpecularColor(diffuse, specular, l->getColor(), c);
        }
        // Transparent objects will pass a bit of light through
        totalLight += tempColor*pathToLight*l->getIntensity();
    }

    totalLight = totalLight/scene.getLightVector().size() + c.getColor() * ambient;
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

    // Skybox hit if no other collision
    if(previousHit == MAXFLOAT){
        return scene.getSkyColor(rayDirection);
    }

    // Return color of the current hit + further reflections/refractions
    return objectColorHit(lastObjectHit, closestC, reflectedRay, scene);
}

/**
 *  Assume there are no objects inside objects -> only refractions between material and air
 * @param shape the object that was hit
 * @param collisionPoint the collision point, for normal calculation
 * @param incoming incoming ray, used to calculate the refracted ray
 * @param scene the total scene used to further calculate collisions
 * @return refracted color, in a recursive way
 */
Vec4 refract(const std::shared_ptr<Shape>& shape, Collision collisionPoint, Ray incoming, const Scene& scene){
    // Calculate the normalized direction
    Vec4 normDir = Vec4::normalize(incoming.getDirectionVector());

    // Calculate index of refraction assuming there is air outside the objects
    double indexOfRefraction;
    if(collisionPoint.isInside()){
        indexOfRefraction = 1/collisionPoint.getRefractiveIndex();
    } else {
        indexOfRefraction = collisionPoint.getRefractiveIndex();
    }

    // Calculate theta with Snell's law
    double theta = sqrt(1-pow(indexOfRefraction, 2)*(1-pow(Vec4::dot(collisionPoint.getNormal(), normDir), 2)));

    // total internal reflection
    if(std::isnan(theta)){
        collisionPoint.setReflectivity(shape->getTransparency());
        return reflect(incoming, collisionPoint, REFLECTIONS, scene);
    }

    // Generate new refracted ray
    Vec4 rayDirection = Vec4::normalize(normDir*indexOfRefraction + collisionPoint.getNormal()*
            (indexOfRefraction*Vec4::dot(normDir, collisionPoint.getNormal())-theta));

    // Start refracted ray little further to avoid self collision
    Ray refractedRay{collisionPoint.getCollisionPoint()+rayDirection*0.1, rayDirection};

    // Check for collisions
    Collision c, closestC;
    std::shared_ptr<Shape> lastObjectHit;
    double previousHit = MAXFLOAT;
    for(auto & object : scene.getObjectVector()) {
        c = object->checkCollision(refractedRay);
        if (previousHit > c.getT() && c.getT() > 0) {
            previousHit = (float) c.getT();
            closestC = c;
            lastObjectHit = object;
        }
    }

    // Skybox hit if no other collision
    if(previousHit == MAXFLOAT){
        return scene.getSkyColor(rayDirection);
    }

    // return combination of light, reflection and refraction at new point
    return objectColorHit(lastObjectHit, closestC, refractedRay, scene);
}

/**
 * For every hit with an object we need to calculate the contributions of light, reflections and refractions
 * @param shape for material properties
 * @param c collision point, for normal calculation and color of the hit
 * @param incoming incoming ray, used to calculate the new reflected and refracted ray
 * @param scene full scene, needed to check for further collisions
 * @return the color of the hit, an accumulation of the light, reflections and refractions
 */
Vec4 objectColorHit(const std::shared_ptr<Shape>& shape, Collision c, Ray incoming, const Scene& scene){
    Vec4 color = {0, 0, 0, 0}, reflection{}, refraction{};

    // For every point calculate the lighting, always present
    color = lighting(shape, c, incoming, scene);

    // Object is reflective
    if(shape->getReflectivity()>EPSILON){
        reflection = reflect(incoming, c, REFLECTIONS, scene)*shape->getReflectivity();
        color += reflection;
    }

    // Object is transparent
    if(shape->getTransparency()>EPSILON){
        refraction = refract(shape, c, incoming, scene)*shape->getTransparency();
        color += refraction;
    }

    return color;
}

void drawPixelsFromVector(std::vector<Vec4>& vector, int begin, int length){
    for(int i = 0; i<length; i++){
        for(int j = 0; j<2*H; j++){
            Vec4 color = vector.at((int)(j+i*(2*H)));
            glColor3d(color.getX(), color.getY(), color.getZ());
            drawDot(begin+i, (int)(-H+j));
        }
        glFlush();
    }
}

void goOverPixels(const Scene& s, std::vector<Vec4>& pixelList, int begin, int end){
    auto camera(s.getCamera());

    // Pre defined variables
    Collision c, lastCollision;
    Ray shotRay{};
    float previousHit;
    Vec4 color{};
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

                // An object was hit
                if(previousHit != MAXFLOAT){
                    // Cumulate color -> anti alias;
                    color += Vec4::clamp(objectColorHit(lastObjectHit, lastCollision, shotRay, s));
                } else { // skybox
                    color += s.getSkyColor(shotRay.getDirectionVector());
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

    // Create pixel vectors -> threads fill these up
    std::vector<std::vector<Vec4>> pixelLists;
    for(int i = 0; i<THREADS; i++){
        pixelLists.emplace_back(std::vector<Vec4>());
    }

    // Create and start the different threads
    std::thread threads[THREADS];
    for(int i = 0; i<THREADS; i++){
     threads[i] = std::thread(goOverPixels, world, std::ref(pixelLists.at(i)), -W+(i*(2*W/THREADS)), -W+(i+1)*(2*W/THREADS));
    }

    int threadsJoined = 0;
    // Check all treads for completion and draw the pixels if completed
    while(threadsJoined != THREADS){
        // Check all threads
        for(int i = 0; i<THREADS; i++){
            // Check completion -> join + draw
            if(threads[i].joinable()){
                threads[i].join();
                drawPixelsFromVector(pixelLists.at(i), (int)(-W+i*(2*W/THREADS)), (int)(2*W/THREADS));
                threadsJoined ++;
            }
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    std::cout << "Time elapsed during rendering: " << duration.count() << " s" << std::endl;
}

// TODO: refraction
// TODO: materials
// TODO: uv-mapping
// TODO: EXTRA: progressive rendering, movable camera, dynamically change the scene using ImGUI
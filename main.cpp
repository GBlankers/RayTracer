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

/**
 * Initialize openGL variables
 */
void openGLInit();

/**
 * Simpler function to draw a pixel to an openGL window
 * @param x x-coordinate
 * @param y y-coordinate
 */
void drawDot(GLint x, GLint y);

/**
 * Code that will be run by openGL to draw pixels to the screen. In this function different threads and the
 * drawing of the screen will be started
 */
void renderer();

/**
 * At a collision calculate the contribution of the light sources to the lighting of the hit.
 * @param c collision point, used for color and material information as well as normal calculation
 * @param scene the total scene.
 * @return the color at the hit, taking into account the lighting components.
 */
Vec4 lighting(const Collision& c, const Scene& scene);

/**
 * Calculate the light and color contribution at a collision point in the scene for reflections.
 * @param c collision point, for normal calculation, color and material of the hit and the incoming ray
 * @param bouncesToDo number of bounces allowed to do, as this function is used in a recursive way we need a way to limit the amount of calls.
 * @param scene the total scene used to further calculate collisions.
 * @return the result of `objectColorHit` at the new collision point or the color of the object that was hit
 */
Vec4 reflect(const Collision& c, int bouncesToDo, const Scene& scene);

/**
 * Calculate the light and color contribution at a collision point in the scene for refractions.
 *  Assume there are no objects inside objects -> only refractions between material and air
 * @param c collision point, for normal calculation, color and material of the hit and the incoming ray
 * @param bouncesToDo number of bounces allowed to do, as this function is used in a recursive way we need a way to limit the amount of calls.
 * @param scene the total scene used to further calculate collisions.
 * @return the result of `objectColorHit` at the new collision point or the color of the object that was hit
 */
Vec4 refract(Collision c, int bouncesToDo, const Scene& scene);

/**
 * For every hit with an object we need to calculate the contributions of light, reflections and refractions
 * @param c collision point, for normal calculation, color and material of the hit and the incoming ray
 * @param bouncesToDo number of bounces allowed to do, as this function is used in a recursive way we need a way to limit the amount of calls.
 * @param scene the total scene used to further calculate collisions.
 * @return the color of the hit, an accumulation of the light, reflections and refractions
 */
Vec4 objectColorHit(Collision& c, int bouncesToDo, const Scene& scene);

/**
 * Go over all the pixels in the vector and draw them to the screen using openGL. The screen is divided vertically. This way
 * we only need to know the vertical coordinates between which we need to draw the pixels.
 * @param vector the vector containing the pixel information
 * @param begin the begin coordinates
 * @param length the length of the divided parts.
 */
void drawPixelsFromVector(std::vector<Vec4>& vector, int begin, int length);

/**
 * Function that does the ray tracing (calculation of the rays, go over all point on the screen, check for collisions and
 * calculate the color and lighting contributions at the collision points. + Anti-aliasing). This function will be multi-threaded
 * so it can't contain any openGL code, purely math. Therefore we also need to give it a list which can be filled with the calculated pixel
 * information
 * @param s the total scene
 * @param pixelList pixel list which will be filled with pixel information
 * @param begin begin coordinates to calculate
 * @param end end coordinates to calculate
 */
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

Vec4 lighting(const Collision& c, const Scene& scene){
    double diffuse, specular, t;
    Vec4 totalLight, tempColor, startPoint;
    double pathToLight;
    Ray r{};

    // Get light components and material at the collision point
    LightComponents lightComponents = c.getLightComponents();
    Material material = c.getMaterial();
    // Get the ambient intensity
    double ambient = lightComponents.ambient;
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
                    pathToLight *= material.transparency;
            }
        }
        // Calculate diffuse and spectral components if there is a clear path to the light source
        if(pathToLight>0){
            diffuse = l->calculateDiffuse(c.getNormal(), c.getCollisionPoint());
            specular = l->calculateSpecular(c.getNormal(), c.getIncoming().getDirectionVector(), c.getCollisionPoint());
            tempColor = l->getColor()*c.getColor()*(lightComponents.diffuse*diffuse +
                    lightComponents.specular*pow(specular, lightComponents.specularExponent));
        }
        // Transparent objects will pass a bit of light through
        totalLight += tempColor*pathToLight*l->getIntensity();
    }

    totalLight = totalLight/(double)scene.getLightVector().size() + c.getColor() * ambient;
    return totalLight;
}

Vec4 reflect(const Collision& c, int bouncesToDo, const Scene& scene){
    // calculate the reflected ray direction
    Vec4 rayDirection = Vec4::normalize(c.getIncoming().getDirectionVector() +
                                        c.getNormal() * (-2) * Vec4::dot(c.getNormal(), c.getIncoming().getDirectionVector()));
    // create the ray, starts at t=0.1 to stop reflections with the object itself
    Ray reflectedRay(c.getCollisionPoint() + rayDirection * 0.1, rayDirection);

    // Check all the world objects for a collision
    Collision tempC, closestC;
    double previousHit = MAXFLOAT;
    for(auto & object : scene.getObjectVector()) {
        tempC = object->checkCollision(reflectedRay);
        if (previousHit > tempC.getT() && tempC.getT() > 0) {
            previousHit = (float) tempC.getT();
            closestC = tempC;
        }
    }

    // Skybox hit if no other collision
    if(previousHit == MAXFLOAT){
        return scene.getSkyColor(rayDirection);
    }

    // Return color of the current hit + further reflections/refractions
    return objectColorHit(closestC, bouncesToDo-1, scene);
}

Vec4 refract(Collision c, int bouncesToDo, const Scene& scene){
    // Calculate the normalized direction
    Vec4 normDir = Vec4::normalize(c.getIncoming().getDirectionVector());

    // Calculate index of refraction assuming there is air outside the objects
    double indexOfRefraction;
    if(c.isInside()){
        indexOfRefraction = 1 / c.getRefractiveIndex();
    } else {
        indexOfRefraction = c.getRefractiveIndex();
    }

    // Calculate theta with Snell's law
    double theta = sqrt(1-pow(indexOfRefraction, 2)*(1-pow(Vec4::dot(c.getNormal(), normDir), 2)));

    // total internal reflection
    if(std::isnan(theta)){
        Material m = c.getMaterial();
        c.setReflectivity(m.transparency);
        return reflect(c, bouncesToDo, scene);
    }

    // Generate new refracted ray
    Vec4 rayDirection = Vec4::normalize(normDir*indexOfRefraction + c.getNormal() *
                                                                    (indexOfRefraction*Vec4::dot(normDir, c.getNormal()) - theta));

    // Start refracted ray little further to avoid self collision
    Ray refractedRay{c.getCollisionPoint() + rayDirection * 0.1, rayDirection};

    // Check for collisions
    Collision tempC, closestC;
    double previousHit = MAXFLOAT;
    for(auto & object : scene.getObjectVector()) {
        tempC = object->checkCollision(refractedRay);
        if (previousHit > tempC.getT() && tempC.getT() > 0) {
            previousHit = (float) c.getT();
            closestC = tempC;
        }
    }

    // Skybox hit if no other collision
    if(previousHit == MAXFLOAT){
        return scene.getSkyColor(rayDirection);
    }

    // return combination of light, reflection and refraction at new point
    return objectColorHit(closestC, bouncesToDo, scene);
}

Vec4 objectColorHit(Collision& c, int bouncesToDo, const Scene& scene){
    Vec4 color, reflection, refraction;
    // material properties will be used to scale the different parts of the color
    Material m = c.getMaterial();
    // For every point calculate the lighting, always present
    color = lighting(c, scene);

    // We need to limit the amount of bounces to eliminate infinite loops between reflective and refractive objects.
    if(bouncesToDo == 0){
        return color;
    }

    // Object is reflective
    if(m.reflectivity>EPSILON){
        // calculate the color of the reflection and scale it using the reflectivity material property
        reflection = reflect(c, bouncesToDo-1, scene)*m.reflectivity;
        // Add the reflection part to the total color
        color += reflection;
    }

    // Object is transparent
    if(m.transparency>EPSILON){
        // calculate the refracted color and scale it using the transparency material property
        refraction = refract(c, bouncesToDo-1, scene)*m.transparency;
        // Add the refraction part to the total color
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
    Vec4 color;

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
                        lastCollision = c;
                    }
                }

                // An object was hit
                if(previousHit != MAXFLOAT){
                    // Cumulate color -> anti alias;
                    color += Vec4::clamp(objectColorHit(lastCollision, BOUNCES, s));
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
    world.fillScene("include/scenes/general.json");

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    // calculate the time for debugging
    auto start = std::chrono::high_resolution_clock::now();

    // Create pixel vectors -> threads fill these up
    std::vector<std::vector<Vec4>> pixelLists;
    // boolean vector to check if a vector is already drawn to the screen
    std::vector<bool> drawn;
    for(int i = 0; i<THREADS; i++){
        pixelLists.emplace_back(std::vector<Vec4>());
        drawn.emplace_back(false);
    }

    // Create and start the different threads
    std::thread threads[THREADS];
    for(int i = 0; i<THREADS; i++){
        // -W+(i*(2*W/THREADS)) and -W+(i+1)*(2*W/THREADS) calculate the pixels that need to be calculated in the thread
        // depending on the total amount of threads and the window width.
        threads[i] = std::thread(goOverPixels, world, std::ref(pixelLists.at(i)), -W+(i*(2*W/THREADS)), -W+(i+1)*(2*W/THREADS));
    }

    // This is not fully math proof -> when W/THREADS does not produce a double then the total number of pixels equals
    // W*H*4/THREADS. But when it does produce a double, there are a little less pixels in every vector due to rounding
    // So to be safe, and to make sure the vectors are drawn, make the number a bit smaller. This does not have a large
    // impact on performance as we still are very close to calculating all the pixels.
    int totalNumberPixels = 4*(W-3)*H/THREADS;

    int threadsJoined = 0;
    // Check all treads for completion and draw the pixels if completed
    while(threadsJoined != THREADS){
        // Check all threads
        for(int i = 0; i<THREADS; i++){
            // Check completion -> join + draw
            if(pixelLists.at(i).size()>= totalNumberPixels and !drawn.at(i)){
                threads[i].join();
                drawPixelsFromVector(pixelLists.at(i), (int)(-W+i*(2*W/THREADS)), (int)(2*W/THREADS));
                threadsJoined ++;
                drawn.at(i) = true;
            }
        }
    }

    // Print duration of rendering for comparisons
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    std::cout << "Time elapsed during rendering: " << duration.count() << " s" << std::endl;
}

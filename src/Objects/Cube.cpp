#include "Cube.h"

Cube::Cube(const Transformation &t, Vec4 color, double ambient, double diffuse, double specular) :
                                                                        Shape(t, color, ambient, diffuse, specular) {}

bool Cube::checkInCube(Ray r, double t){
    Vec4 collisionPoint = r.at(t);

    if (fabs(collisionPoint.getX()) <= (1+EPSILON) &&
        fabs(collisionPoint.getY()) <= (1+EPSILON) &&
        fabs(collisionPoint.getZ()) <= (1+EPSILON)) {
        return true;
    }
    return false;
}

Collision Cube::checkCollision(Ray r) {
    double t;

    // there is a hit -> calculate shading
    if(checkHit(r, t)){
        return {r.at(t), t, this->getColor()};
    }

    return {{0,0,0,0}, -1, {0, 0, 0, 0}};
}

Vec4 Cube::calculateNormal(Vec4 hitPoint) {
    double x = hitPoint.getX(), y = hitPoint.getY(), z = hitPoint.getZ();
    double nx=0, ny=0, nz=0;
    if(x >= (1-EPSILON) || x <= (-1+EPSILON)){
        nx = x;
    }
    if(y >= (1-EPSILON) || y <= (-1+EPSILON)){
        ny = y;
    }
    if(z >= (1-EPSILON) || z <= (-1+EPSILON)){
        nz = z;
    }
    return {nx, ny, nz, 0};
}

bool Cube::checkHit(Ray r, double &t) {
    // Inverse transform the ray and the light source
    Matrix4 inverse = this->getT().getInverse();
    Ray transformedRay = r.transform(inverse);

    double tempT0, tempT1;
    bool hit = false;
    t = MAXFLOAT;

    // Implementation looks weird, but it works and is faster than implementing it using transformed planes
    // intersection with plane 0 and plane 1:
    // If the direction vector is 0 then the ray is parallel to the plane so there will never be a hit
    if(fabs(transformedRay.getDirectionVector().getY()) > EPSILON){
        // Combination of equations of a plane and of a ray -> There will be 1 equation to calculate t
        tempT0 = (transformedRay.getStartPoint().getY()+1)/(-transformedRay.getDirectionVector().getY());
        tempT1 = (transformedRay.getStartPoint().getY()-1)/(-transformedRay.getDirectionVector().getY());

        // Check if the t is bigger than 0 -> there is a hit in front of the eye
        // take the smallest t of the 2 -> closest to the eye
        // if tempT is negative then the hit is not in front of the eye
        if(tempT0 > 0 and tempT0 <= t) {
            // check if the current hit is in the cube
            if (checkInCube(transformedRay, tempT0)){
                hit = true;
                t = tempT0;
            }
        }
        if (tempT1 > 0 and tempT1 <= t){
            if(checkInCube(transformedRay, tempT1)){
                hit = true;
                t = tempT1;
            }
        }
    }
    // intersection with plane 2 and 3
    if(fabs(transformedRay.getDirectionVector().getZ()) > EPSILON){
        tempT0 = (transformedRay.getStartPoint().getZ()+1)/(-transformedRay.getDirectionVector().getZ());
        tempT1 = (transformedRay.getStartPoint().getZ()-1)/(-transformedRay.getDirectionVector().getZ());

        if(tempT0 > 0 and tempT0 <= t) {
            // check if the current hit is in the cube
            if (checkInCube(transformedRay, tempT0)){
                hit = true;
                t = tempT0;
            }
        }
        if (tempT1 > 0 and tempT1 <= t){
            if(checkInCube(transformedRay, tempT1)){
                hit = true;
                t = tempT1;
            }
        }
    }
    // intersection with plane 4 and 5
    if(fabs(transformedRay.getDirectionVector().getX()) > EPSILON){
        tempT0 = (transformedRay.getStartPoint().getX()+1)/(-transformedRay.getDirectionVector().getX());
        tempT1 = (transformedRay.getStartPoint().getX()-1)/(-transformedRay.getDirectionVector().getX());

        if(tempT0 > 0 and tempT0 <= t) {
            // check if the current hit is in the cube
            if (checkInCube(transformedRay, tempT0)){
                hit = true;
                t = tempT0;
            }
        }
        if (tempT1 > 0 and tempT1 <= t){
            if(checkInCube(transformedRay, tempT1)){
                hit = true;
                t = tempT1;
            }
        }
    }
    return hit;
}

bool Cube::checkHit(Ray r){
    // Inverse transform the ray and the light source
    Matrix4 inverse = this->getT().getInverse();
    Ray transformedRay = r.transform(inverse);

    double tempT0, tempT1;
    double t = MAXFLOAT;

    // Implementation looks weird, but it works and is faster than implementing it using transformed planes
    // intersection with plane 0 and plane 1:
    // If the direction vector is 0 then the ray is parallel to the plane so there will never be a hit
    if(fabs(transformedRay.getDirectionVector().getY()) > EPSILON){
        // Combination of equations of a plane and of a ray -> There will be 1 equation to calculate t
        tempT0 = (transformedRay.getStartPoint().getY()+1)/(-transformedRay.getDirectionVector().getY());
        tempT1 = (transformedRay.getStartPoint().getY()-1)/(-transformedRay.getDirectionVector().getY());

        // Check if the t is bigger than 0 -> there is a hit in front of the eye
        // take the smallest t of the 2 -> closest to the eye
        // if tempT is negative then the hit is not in front of the eye
        if(tempT0 > 0 and tempT0 <= t) {
            // check if the current hit is in the cube
            if (checkInCube(transformedRay, tempT0)){
                return true;
            }
        }
        if (tempT1 > 0 and tempT1 <= t){
            if(checkInCube(transformedRay, tempT1)){
                return true;
            }
        }
    }
    // intersection with plane 2 and 3
    if(fabs(transformedRay.getDirectionVector().getZ()) > EPSILON){
        tempT0 = (transformedRay.getStartPoint().getZ()+1)/(-transformedRay.getDirectionVector().getZ());
        tempT1 = (transformedRay.getStartPoint().getZ()-1)/(-transformedRay.getDirectionVector().getZ());

        if(tempT0 > 0 and tempT0 <= t) {
            // check if the current hit is in the cube
            if (checkInCube(transformedRay, tempT0)){
                return true;
            }
        }
        if (tempT1 > 0 and tempT1 <= t){
            if(checkInCube(transformedRay, tempT1)){
                return true;
            }
        }
    }
    // intersection with plane 4 and 5
    if(fabs(transformedRay.getDirectionVector().getX()) > EPSILON){
        tempT0 = (transformedRay.getStartPoint().getX()+1)/(-transformedRay.getDirectionVector().getX());
        tempT1 = (transformedRay.getStartPoint().getX()-1)/(-transformedRay.getDirectionVector().getX());

        if(tempT0 > 0 and tempT0 <= t) {
            // check if the current hit is in the cube
            if (checkInCube(transformedRay, tempT0)){
                return true;
            }
        }
        if (tempT1 > 0 and tempT1 <= t){
            if(checkInCube(transformedRay, tempT1)){
                return true;
            }
        }
    }
    return false;
}

double Cube::shadowDiffuseSpecular(Vec4 hitPoint, std::vector<std::shared_ptr<LightSource>> l,
                                   std::vector<std::shared_ptr<Shape>> worldObjects) {
    double intensity = 0, maxIntensity = 0;
    bool clearPathToLight;

    for(const auto& light: l){
        // Calculate the max possible intensity
        maxIntensity += light->getIntensity();
        // Assume there is a clear path to the light source
        clearPathToLight = true;
        // Go over all the objects in the world
        for(const auto& obj: worldObjects){
            // Do not check the for an intersection with itself
            // + check if the light is blocked by other objects
            if(obj.get() != this and obj->checkHit(Ray{hitPoint, light->getPosition() - hitPoint})) {
                // There is no clear path to the light -> there will be shadows
                clearPathToLight = false;
            }
        }
        // If there is a clear path -> calculate the diffuse and specular components
        if(clearPathToLight){
            // Inverse transform the light source
            Matrix4 inverseTransform = this->getT().getInverse();
            light->transform(inverseTransform);
            // Calculate the diffuse component
            intensity += this->getDiffuse()*light->calculateDiffuse(
                    calculateNormal(inverseTransform * hitPoint),inverseTransform * hitPoint);

        }
    }

    return 0;
}

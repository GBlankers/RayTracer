#include "Cube.h"

bool Cube::checkInCube(Ray r, double t){
    Vec4 collisionPoint = r.at(t);

    if (fabs(collisionPoint.getX()) <= (1+tolerance) &&
        fabs(collisionPoint.getY()) <= (1+tolerance) &&
        fabs(collisionPoint.getZ()) <= (1+tolerance)) {
        return true;
    }
    return false;
}

Cube::Cube(const Transformation &t, Vec4 color) : Shape(t, color) {}

Collision Cube::checkCollision(Ray r, std::vector<std::shared_ptr<LightSource>> l, std::vector<std::shared_ptr<Shape>> worldObjects) {
    // Inverse transform the ray and the light source
    Matrix4 inverse = this->getT().getInverse();
    Ray transformedRay = r.transform(inverse);

    // Calculate the intersection with a cube from (-/+1, -/+1, -/+1) centered around (0,0,0)
    double tempT0, tempT1,t = MAXFLOAT;
    bool hit = false;

    // Implementation looks weird, but it works and is faster than implementing it using transformed planes
    // intersection with plane 0 and plane 1:
    // If the direction vector is 0 then the ray is parallel to the plane so there will never be a hit
    if(transformedRay.getDirectionVector().getY() != 0.0){
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
    if(transformedRay.getDirectionVector().getZ() != 0.0){
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
    if(transformedRay.getDirectionVector().getX() != 0.0){
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

    // there is a hit -> calculate shading
    if(hit){
        // Calculate hit point in local coordinates
        Vec4 hitPointL = transformedRay.at(t);
        // Calculate hit point in world coordinates
        Vec4 hitPointW = r.at(t);
        // Keep track of total intensity
        double intensity = 0;
        // Is there a clear path to the light source
        bool clearPathToLight;

        // Check all the light sources
        for(const auto& light: l){
            // For every light source, assume that there is a clear path at first
            clearPathToLight = true;
            // Check all the objects in the scene
            for(const auto& obj: worldObjects){
                // Do not check the for an intersection with itself
                // + check if the light is blocked by other objects
                if(obj.get() != this and obj->checkHit(Ray{hitPointW, light->getPosition() - hitPointW})) {
                    // There is no clear path to the light -> there will be shadows
                    clearPathToLight = false;
                }
            }
            if(clearPathToLight) {
                light->transform(inverse);
                intensity += light->calculateIntensity(calculateNormal(hitPointL), hitPointL);
            }
        }

        return {hitPointW, t, getIntensityCorrectedColor(hitPointL, intensity / (double)l.size())};
    }

    return {{0,0,0,0}, -1, {0, 0, 0, 0}};
}

Vec4 Cube::calculateNormal(Vec4 hitPoint) {
    double x = hitPoint.getX(), y = hitPoint.getY(), z = hitPoint.getZ();
    double nx=0, ny=0, nz=0;
    if(x >= (1-tolerance) || x <= (-1+tolerance)){
        nx = x;
    }
    if(y >= (1-tolerance) || y <= (-1+tolerance)){
        ny = y;
    }
    if(z >= (1-tolerance) || z <= (-1+tolerance)){
        nz = z;
    }
    return {nx, ny, nz, 0};
}

bool Cube::checkHit(Ray r) {
    // Inverse transform the ray and the light source
    Matrix4 inverse = this->getT().getInverse();
    Ray transformedRay = r.transform(inverse);

    double tempT0, tempT1;

    if(transformedRay.getDirectionVector().getY() != 0.0){
        // Combination of equations of a plane and of a ray -> There will be 1 equation to calculate t
        tempT0 = (transformedRay.getStartPoint().getY()+1)/(-transformedRay.getDirectionVector().getY());
        tempT1 = (transformedRay.getStartPoint().getY()-1)/(-transformedRay.getDirectionVector().getY());

        // Check if the t is bigger than 0 -> there is a hit in front of the eye
        // take the smallest t of the 2 -> closest to the eye
        // if tempT is negative then the hit is not in front of the eye
        if(tempT0 > 0) {
            // check if the current hit is in the cube
            if (checkInCube(transformedRay, tempT0)){
                return true;
            }
        }
        if (tempT1 > 0){
            if(checkInCube(transformedRay, tempT1)){
                return true;
            }
        }
    }
    // intersection with plane 2 and 3
    if(transformedRay.getDirectionVector().getZ() != 0.0){
        tempT0 = (transformedRay.getStartPoint().getZ()+1)/(-transformedRay.getDirectionVector().getZ());
        tempT1 = (transformedRay.getStartPoint().getZ()-1)/(-transformedRay.getDirectionVector().getZ());

        if(tempT0 > 0) {
            // check if the current hit is in the cube
            if (checkInCube(transformedRay, tempT0)){
                return true;
            }
        }
        if (tempT1 > 0){
            if(checkInCube(transformedRay, tempT1)){
                return true;
            }
        }
    }
    // intersection with plane 4 and 5
    if(transformedRay.getDirectionVector().getX() != 0.0){
        tempT0 = (transformedRay.getStartPoint().getX()+1)/(-transformedRay.getDirectionVector().getX());
        tempT1 = (transformedRay.getStartPoint().getX()-1)/(-transformedRay.getDirectionVector().getX());

        if(tempT0 > 0) {
            // check if the current hit is in the cube
            if (checkInCube(transformedRay, tempT0)){
                return true;
            }
        }
        if (tempT1 > 0){
            if(checkInCube(transformedRay, tempT1)){
                return true;
            }
        }
    }

    return false;
}

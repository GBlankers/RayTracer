#include "Cube.h"

Cube::Cube(const Transformation &t, Vec4 color, double ambient, double diffuse, double specular,
           double specularComponent, double reflectivity, double roughness, double transparency, double refractiveIndex) :
        Shape(t, color, ambient, diffuse, specular, specularComponent, reflectivity, roughness, transparency, refractiveIndex) {}

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
    bool inside;

    // there is a hit -> calculate shading
    if(checkHit(r, t, inside)){
        return {r.at(t), t, getColor(), Vec4::normalize(calculateNormal(r.at(t), inside) +
        Vec4::random(-0.5, 0.5) * getRoughness()), inside, getReflectivity(), getTransparency(), getRefractiveIndex()};
    }

    return {{0, 0, 0, 0}, -1, {0, 0, 0, 0}, {0, 0, 0, 0},false, 0, 0, 0};
}


/**
 * Calculate the normal in world coordinates
 * @param hitPoint the hit point in world coordinates
 * @param inside if the hit is on the inside, we need to flip the normal
 * @return the normal direction at the hit point in world coordinates
 */
Vec4 Cube::calculateNormal(Vec4 hitPoint, bool inside) {
    Vec4 inverseHitPoint = getT().getInverse()*hitPoint;
    double x = inverseHitPoint.getX(), y = inverseHitPoint.getY(), z = inverseHitPoint.getZ();
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

    if(inside)
        return Vec4::normalize(getT().getForward()*Vec4{nx, ny, nz, 0})*-1;
    return Vec4::normalize(getT().getForward()*Vec4{nx, ny, nz, 0});
}

bool Cube::checkHit(Ray r, double &t, bool &inside) {
    // Inverse transform the ray and the light source
    Matrix4 inverse = getT().getInverse();
    Ray transformedRay = r.transform(inverse);

    if(checkInCube(transformedRay, 0)){
        inside = true;
    } else {
        inside = false;
    }

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

bool Cube::checkHit(Ray r, double &t) {
    // Inverse transform the ray and the light source
    Matrix4 inverse = getT().getInverse();
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
    Matrix4 inverse = getT().getInverse();
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

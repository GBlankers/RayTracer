#include "Cube.h"

#include <utility>

Cube::Cube(const Transformation &t, LightComponents lightComponents, Material material) :
        Shape(t, LightComponents(std::move(lightComponents)), Material(std::move(material))) {}

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
        double red, green, blue;
        LightComponents l = this->lightComponents;
        Vec4 hit = r.at(t);
        this->getColor(hit, red, green, blue);
        l.color = new SingleColor(Vec4{red, green, blue, 0});

        return {r, t, calculateNormal(r.at(t), inside), inside, l, this->material};
    }

    return {};
}

bool Cube::checkHit(Ray r, double &t, bool &inside) {
    // Inverse transform the ray and the light source
    Matrix4 inverse = getTransformation().getInverse();
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
    Matrix4 inverse = getTransformation().getInverse();
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

/**
 * Calculate the normal in world coordinates
 * @param hitPoint the hit point in world coordinates
 * @param inside if the hit is on the inside, we need to flip the normal
 * @return the normal direction at the hit point in world coordinates
 */
Vec4 Cube::calculateNormal(Vec4 hitPoint, bool inside) {
    Vec4 inverseHitPoint = getTransformation().getInverse() * hitPoint;
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
        return Vec4::normalize((getTransformation().getForward() * Vec4{nx, ny, nz, 0}) + Vec4::random(-0.5, 0.5) * material.roughness) * -1;
    return Vec4::normalize((getTransformation().getForward() * Vec4{nx, ny, nz, 0}) + Vec4::random(-0.5, 0.5) * material.roughness);
}

void Cube::getColor(Vec4 hitPoint, double &r, double &g, double &b) {
    // uv-map
    Vec4 hit = t.getInverse()*hitPoint;
    // Get color components -> no uv-map -> 0, 0
    Vec4 c = lightComponents.color->getColor("cube", 0, 0);
    r = c.getX();
    g = c.getY();
    b = c.getZ();
}

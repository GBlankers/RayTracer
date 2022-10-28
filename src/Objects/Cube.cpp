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
        Vec4 hitPoint = transformedRay.at(t);
        // calculate the intensity of the light
        double intensity = 0;
        std::vector<bool> hitVector;
        for(const auto& light: l){
            light->transform(inverse);
            for(const auto& s: worldObjects){
                if(s.get() != this)
                    hitVector.push_back(s->checkHit(Ray{hitPoint, light->getPosition()-hitPoint}));
            }
            if(!std::count(hitVector.begin(), hitVector.end(), true))
                intensity += light->calculateIntensity(calculateNormal(hitPoint), hitPoint);
        }

        return {r.at(t), t, getIntensityCorrectedColor(hitPoint, intensity/(double)l.size())};
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
    return false;
}

#include "Cube.h"

bool Cube::checkInCube(Ray r, double t){
    Vec4 collisionPoint = r.getStartPoint()+(r.getDirectionVector()*t);
    if (collisionPoint.getX() >= -1 && collisionPoint.getX() <= 1 &&
        collisionPoint.getY() >= -1 && collisionPoint.getY() <= 1 &&
        collisionPoint.getZ() >= -1 && collisionPoint.getZ() <= 1) {
        return true;
    }
    return false;
}

Cube::Cube(const Transformation &t, double r, double g, double b) : Shape(t, r, g, b) {}

Collision Cube::checkCollision(Ray r, LightSource l) {
    // Inverse transform the ray and the light source
    Matrix4 inverse = this->getT().getInverse();
    Ray transformedRay = r.transform(inverse);
    LightSource transformedLight = l.transform(inverse);

    // Calculate the intersection with a cube from (-/+1, -/+1, -/+1) centered around (0,0,0)
    double tempT0, tempT1, t = -1;
    // intersection with plane 0 and plane 1:
    // If the direction vector is 0 then the ray is parallel to the plane so there will never be a hit
    if(transformedRay.getDirectionVector().getY() != 0.0){
        // Combination of equations of a plane and of a ray -> There will be 1 equation to calculate t
        tempT0 = (transformedRay.getStartPoint().getY()+1)/(-transformedRay.getDirectionVector().getY());
        tempT1 = (transformedRay.getStartPoint().getY()-1)/(-transformedRay.getDirectionVector().getY());

        // Check if the t is bigger than 0 -> there is a hit in front of the eye
        // take the smallest t of the 2 -> closest to the eye
        // if tempT is negative then the hit is not in front of the eye
        if(tempT0 > 0 && tempT0 < tempT1){
            // check if the current hit is in the cube
            if(checkInCube(transformedRay, tempT0))
                t = tempT0;
        } else if (tempT1 > 0 && tempT1 < tempT0){
            if(checkInCube(transformedRay, tempT1))
                t = tempT1;
        }
    }
    // intersection with plane 2 and 3
    if(transformedRay.getDirectionVector().getZ() != 0.0){
        tempT0 = (transformedRay.getStartPoint().getZ()+1)/(-transformedRay.getDirectionVector().getZ());
        tempT1 = (transformedRay.getStartPoint().getZ()-1)/(-transformedRay.getDirectionVector().getZ());

        // if the t is still negative then we can loosen the requirements for a hit
        if(t==-1){
            if(tempT0 > 0 && tempT0 < tempT1){
                if(checkInCube(transformedRay, tempT0))
                    t = tempT0;
            } else if (tempT1 > 0 && tempT1 < tempT0){
                if(checkInCube(transformedRay, tempT1))
                    t = tempT1;
            }
        } else { // if there is a t we need to check if the tempT is bigger than 0 and smaller than the current t
            if (tempT0 > 0 && tempT0 < t){
                if(checkInCube(transformedRay, tempT0))
                    t = tempT0;
            }
            if (tempT1 > 0 && tempT1 < t){
                if(checkInCube(transformedRay, tempT1))
                    t = tempT1;
            }
        }
    }
    // intersection with plane 4 and 5
    if(transformedRay.getDirectionVector().getX() != 0.0){
        tempT0 = (transformedRay.getStartPoint().getX()+1)/(-transformedRay.getDirectionVector().getX());
        tempT1 = (transformedRay.getStartPoint().getX()-1)/(-transformedRay.getDirectionVector().getX());
        if(t==-1){
            if(tempT0 > 0 && tempT0 < tempT1){
                if(checkInCube(transformedRay, tempT0))
                    t = tempT0;
            }
            if (tempT1 > 0 && tempT1 < tempT0){
                if(checkInCube(transformedRay, tempT1))
                    t = tempT1;
            }
        } else {
            if (tempT0 > 0 && tempT0 < t){
                if(checkInCube(transformedRay, tempT0))
                    t = tempT0;
            }
            if (tempT1 > 0 && tempT1 < t){
                if(checkInCube(transformedRay, tempT1))
                    t = tempT1;
            }
        }
    }

    // there is a hit -> calculate shading
    if(t>-1){
        // Calculate hit point in local coordinates
        Vec4 hit = transformedRay.getStartPoint()+(transformedRay.getDirectionVector()*t);
        // Calculate the normal vector at that point
        Vec4 normal = calculateNormal(hit);

        double intensity = l.calculateIntensity(normal, hit);

        return {r.getStartPoint()+(r.getDirectionVector()*t), t, this->getR()*intensity, this->getG()*intensity,
                this->getB()*intensity};
    }

    return {{0,0,0,0}, -1, 0, 0, 0};
}

Vec4 Cube::calculateNormal(Vec4 hitPoint) {
    double x = hitPoint.getX(), y = hitPoint.getY(), z = hitPoint.getZ();
    double nx=0, ny=0, nz=0;
    if(x == 1 || x == -1){
        nx = x;
    }
    if(y == 1 || y == -1){
        ny = y;
    }
    if(z == 1 || z == -1){
        nz = z;
    }
    return {nx, ny, nz, 0};
}

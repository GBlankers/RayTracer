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

void Cube::give2Smallest(std::vector<double> tList, double &t1, double &t2) {
    if(tList.empty()){t1 = -1; t2 = -1; return;}
    if(tList.size() == 1){t1 = tList[0]; t2 = -1; return;}
    std::sort(tList.begin(), tList.end());
    t1 = tList[0];
    t2 = tList[1];
}

Collision Cube::checkCollision(Ray r) {
    double t, t2;
    bool inside;

    // there is a hit -> calculate shading
    if(checkHit(r, t, inside, t2)){
        double red, green, blue;
        LightComponents l = this->lightComponents;
        Vec4 hit = r.at(t);
        this->getColor(hit, red, green, blue);
        l.color = new SingleColor(Vec4{red, green, blue, 0});

        return {r, t, calculateNormal(r.at(t), inside), inside, l, this->material, t2};
    }

    return {};
}

bool Cube::checkHit(Ray r, double &t, bool &inside, double &t2) {
    // Inverse transform the ray and the light source
    Matrix4 inverse = getTransformation().getInverse();
    Ray transformedRay = r.transform(inverse);

    if(checkInCube(transformedRay, 0)){
        inside = true;
    } else {
        inside = false;
    }

    double tempT0, tempT1, tempT2, tempT3, tempT4, tempT5;
    std::vector<double> tList;

    // Implementation looks weird, but it works and is faster than implementing it using transformed planes
    // intersection with plane 0 and plane 1:
    // If the direction vector is 0 then the ray is parallel to the plane so there will never be a hit
    if(fabs(transformedRay.getDirectionVector().getY()) > EPSILON){
        // Combination of equations of a plane and of a ray -> There will be 1 equation to calculate t
        tempT0 = (transformedRay.getStartPoint().getY()+1)/(-transformedRay.getDirectionVector().getY());
        tempT1 = (transformedRay.getStartPoint().getY()-1)/(-transformedRay.getDirectionVector().getY());

        if(tempT0>0 and checkInCube(transformedRay, tempT0)) tList.emplace_back(tempT0);
        if(tempT1>0 and checkInCube(transformedRay, tempT1)) tList.emplace_back(tempT1);
    }
    // intersection with plane 2 and 3
    if(fabs(transformedRay.getDirectionVector().getZ()) > EPSILON){
        tempT2 = (transformedRay.getStartPoint().getZ()+1)/(-transformedRay.getDirectionVector().getZ());
        tempT3 = (transformedRay.getStartPoint().getZ()-1)/(-transformedRay.getDirectionVector().getZ());

        if(tempT2>0 and checkInCube(transformedRay, tempT2)) tList.emplace_back(tempT2);
        if(tempT3>0 and checkInCube(transformedRay, tempT3)) tList.emplace_back(tempT3);
    }
    // intersection with plane 4 and 5
    if(fabs(transformedRay.getDirectionVector().getX()) > EPSILON){
        tempT4 = (transformedRay.getStartPoint().getX()+1)/(-transformedRay.getDirectionVector().getX());
        tempT5 = (transformedRay.getStartPoint().getX()-1)/(-transformedRay.getDirectionVector().getX());

        if(tempT4>0 and checkInCube(transformedRay, tempT4)) tList.emplace_back(tempT4);
        if(tempT5>0 and checkInCube(transformedRay, tempT5)) tList.emplace_back(tempT5);
    }

    give2Smallest(tList, t, t2);

    return !tList.empty();
}

bool Cube::checkHit(Ray r, double &t) {
// Inverse transform the ray and the light source
    Matrix4 inverse = getTransformation().getInverse();
    Ray transformedRay = r.transform(inverse);

    double tempT0, tempT1, tempT2, tempT3, tempT4, tempT5;
    std::vector<double> tList;

    // Implementation looks weird, but it works and is faster than implementing it using transformed planes
    // intersection with plane 0 and plane 1:
    // If the direction vector is 0 then the ray is parallel to the plane so there will never be a hit
    if(fabs(transformedRay.getDirectionVector().getY()) > EPSILON){
        // Combination of equations of a plane and of a ray -> There will be 1 equation to calculate t
        tempT0 = (transformedRay.getStartPoint().getY()+1)/(-transformedRay.getDirectionVector().getY());
        tempT1 = (transformedRay.getStartPoint().getY()-1)/(-transformedRay.getDirectionVector().getY());

        if(tempT0>0 and checkInCube(transformedRay, tempT0)) tList.emplace_back(tempT0);
        if(tempT1>0 and checkInCube(transformedRay, tempT1)) tList.emplace_back(tempT1);
    }
    // intersection with plane 2 and 3
    if(fabs(transformedRay.getDirectionVector().getZ()) > EPSILON){
        tempT2 = (transformedRay.getStartPoint().getZ()+1)/(-transformedRay.getDirectionVector().getZ());
        tempT3 = (transformedRay.getStartPoint().getZ()-1)/(-transformedRay.getDirectionVector().getZ());

        if(tempT2>0 and checkInCube(transformedRay, tempT2)) tList.emplace_back(tempT2);
        if(tempT3>0 and checkInCube(transformedRay, tempT3)) tList.emplace_back(tempT3);
    }
    // intersection with plane 4 and 5
    if(fabs(transformedRay.getDirectionVector().getX()) > EPSILON){
        tempT4 = (transformedRay.getStartPoint().getX()+1)/(-transformedRay.getDirectionVector().getX());
        tempT5 = (transformedRay.getStartPoint().getX()-1)/(-transformedRay.getDirectionVector().getX());

        if(tempT4>0 and checkInCube(transformedRay, tempT4)) tList.emplace_back(tempT4);
        if(tempT5>0 and checkInCube(transformedRay, tempT5)) tList.emplace_back(tempT5);
    }

    return !tList.empty();
}

/**
 * Calculate the normal in world coordinates
 * @param hitPoint the hit point in world coordinates
 * @param inside if the hit is on the inside, we need to flip the normal
 * @return the normal direction at the hit point in world coordinates
 */
Vec4 Cube::calculateNormal(Vec4 hitPoint, bool inside) {
    Vec4 localHit = t.getInverse() * hitPoint;
    // Calculate normal in local coordinates + uv-mapping
    double nx=0, ny=0, nz=0, u = 0, v = 0;
    if(localHit.getX() >= (1-EPSILON) or localHit.getX() <= (-1+EPSILON)){
        nx = localHit.getX();
        u = (1+localHit.getY())/2;
        v = (1+localHit.getZ())/2;
    }
    if(localHit.getY() >= (1-EPSILON) or localHit.getY() <= (-1+EPSILON)){
        ny = localHit.getY();
        u = (1+localHit.getX())/2;
        v = (1+localHit.getZ())/2;
    }
    if(localHit.getZ() >= (1-EPSILON) or localHit.getZ() <= (-1+EPSILON)){
        nz = localHit.getZ();
        u = (1+localHit.getX())/2;
        v = (1+localHit.getY())/2;
    }
    Vec4 normal = inside ? Vec4{nx, ny, nz, 0} * -1 : Vec4{nx, ny, nz, 0};
    // Manipulate normal + transform to world coordinates + normalize
    return Vec4::normalize(t.getForward()*material.manipulateNormal(normal, u, v, hitPoint));
}

void Cube::getColor(Vec4 hitPoint, double &r, double &g, double &b) {
    Vec4 localHit = t.getInverse()*hitPoint;
    // uv-map
    double u, v;
    if(localHit.getZ() <= (-1+EPSILON) or localHit.getZ() >= (1-EPSILON)){
        u = (1+localHit.getX())/2;
        v = (1+localHit.getY())/2;
    } else if(localHit.getY() <= (-1+EPSILON) or localHit.getY() >= (1-EPSILON)){
        u = (1+localHit.getX())/2;
        v = (1+localHit.getZ())/2;
    } else {
        u = (1+localHit.getY())/2;
        v = (1+localHit.getZ())/2;
    }
    // Get color components
    Vec4 c = lightComponents.color->getColor(u, v, localHit, hitPoint);
    r = c.getX();
    g = c.getY();
    b = c.getZ();
}

SingleColor* Cube::getBooleanDifferenceColor(Vec4 hitPoint, LightComponents l) {
    Vec4 localHit = t.getInverse()*hitPoint;
    // uv-map
    double u, v;
    if(localHit.getZ() <= (-1+EPSILON) or localHit.getZ() >= (1-EPSILON)){
        u = (1+localHit.getX())/2;
        v = (1+localHit.getY())/2;
    } else if(localHit.getY() <= (-1+EPSILON) or localHit.getY() >= (1-EPSILON)){
        u = (1+localHit.getX())/2;
        v = (1+localHit.getZ())/2;
    } else {
        u = (1+localHit.getY())/2;
        v = (1+localHit.getZ())/2;
    }
    // Get color components
    Vec4 c = l.color->getColor(u, v, localHit, hitPoint);
    return new SingleColor({c.getX(), c.getY(), c.getZ(), 0});
}

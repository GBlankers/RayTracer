#include "Plane.h"

Plane::Plane(const Transformation &t, LightComponents lightComponents, Material material) :
        Shape(t, LightComponents(std::move(lightComponents)), Material(std::move(material))) {}

// Default plane at y=0 and limited between -1 and 1 for x and z
Collision Plane::checkCollision(Ray r) {
    double t;
    bool inside;

    if(checkHit(r, t, inside)){
        Vec4 hit = r.at(t);
        LightComponents l = this->lightComponents;
        double red, green, blue;
        this->getColor(hit, red, green, blue);
        l.color = new SingleColor(Vec4{red, green, blue, 0});

        return {r, t, calculateNormal(hit, inside), inside, l, material};
    }

    return {};
}

bool Plane::checkHit(Ray r, double &t, bool &inside) {
    // assume the plane is infinitely thin
    inside = false;
    return checkHit(r, t);
}

bool Plane::checkHit(Ray r, double &t) {
    // Inverse transform the ray and the light source
    Matrix4 inverse = getTransformation().getInverse();
    Ray transformedRay = r.transform(inverse);
    // Ray is not parallel to the plane
    if(fabs(transformedRay.getDirectionVector().getY()) > EPSILON){
        t = -transformedRay.getStartPoint().getY()/transformedRay.getDirectionVector().getY();
        // Check if -1<x<1 and -1<z<1
        Vec4 localHit = transformedRay.at(t);
        if(localHit.getX()>=-1 and localHit.getX()<=1 and localHit.getZ()>=-1 and localHit.getZ()<=1){
            return t>0;
        }
    }
    return false;
}

/**
 * Override the virtual calculate normal function to calculate the normal for the plane
 * @param hitPoint hit point in world coordinates
 * @param inside check if the hit is inside the object
 * @return the normal in world coordinates
 */
Vec4 Plane::calculateNormal(Vec4 hitPoint, bool inside) {
    // Calculate normal in local coordinates
    Vec4 normal = inside ? Vec4{0, -1, 0, 0} : Vec4{0, 1, 0, 0};
    // uv-mapping
    Vec4 localHit = t.getInverse()*hitPoint;
    double u = (localHit.getX()+1)/2;
    double v = (localHit.getZ()+1)/2;
    // Manipulate normal + transform to world coordinates + normalize
    return Vec4::normalize(t.getForward()*material.manipulateNormal(normal, u, v, hitPoint));
}

void Plane::getColor(Vec4 hitPoint, double &r, double &g, double &b) {
    // uv-map
    Vec4 localHit = t.getInverse() * hitPoint;
    double u = (localHit.getX()+1)/2;
    double v = (localHit.getZ()+1)/2;
    // Get color components
    Vec4 c = lightComponents.color->getColor(u, v, localHit, hitPoint);
    r = c.getX();
    g = c.getY();
    b = c.getZ();
}

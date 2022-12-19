#include "Plane.h"

Plane::Plane(const Transformation &t, LightComponents lightComponents, Material material) :
        Shape(t, LightComponents(std::move(lightComponents)), Material(std::move(material))) {}

Plane::Plane(const Transformation &t, const std::string& path, LightComponents lightComponents, Material material) :
        Shape(t, path, LightComponents(std::move(lightComponents)), Material(std::move(material))) {}

// Default plane at y=0
Collision Plane::checkCollision(Ray r) {
    double t;
    bool inside;

    if(checkHit(r, t, inside)){
        Vec4 hit = r.at(t);
        LightComponents l = this->lightComponents;
        if(checkerBoard){
            bool check;
            Vec4 localHit = getTransformation().getInverse() * hit;
            if(localHit.getX()<0){
                if(localHit.getZ()<0){
                    check = (((int)fabs(localHit.getX())/checkerBoardSize) + ((int)fabs(localHit.getZ())/checkerBoardSize)) % 2 == 0;
                } else {
                    check = (((int)fabs(localHit.getX())/checkerBoardSize) + ((int)fabs(localHit.getZ())/checkerBoardSize)) % 2 == 1;
                }
            } else {
                if(localHit.getZ()<0){
                    check = (((int)fabs(localHit.getX())/checkerBoardSize) + ((int)fabs(localHit.getZ())/checkerBoardSize)) % 2 == 1;
                } else {
                    check = (((int)fabs(localHit.getX())/checkerBoardSize) + ((int)fabs(localHit.getZ())/checkerBoardSize)) % 2 == 0;
                }
            }
            if(check){
                l.color = {};
                return {r, t, calculateNormal(r.at(t), inside), inside, l, this->material};
            }
        }
        double red, green, blue;
        this->getColor(hit, red, green, blue);
        l.color = {red, green, blue, 0};

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
        Vec4 hit = transformedRay.at(t);
        if(-1<hit.getX() and hit.getX()<1 and -1<hit.getX() and hit.getX()<1){
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

void Plane::setCheckerBoardPattern(bool b, int size) {
    this->checkerBoard = b;
    this->checkerBoardSize = size;
}

void Plane::getColor(Vec4 hitPoint, double &r, double &g, double &b) {
    if(image.empty()){
        Shape::getColor(hitPoint, r, g, b);
    } else {
        Vec4 localHit = t.getInverse()*hitPoint;

        double u = (localHit.getX()+1)/2;
        double v = (localHit.getZ()+1)/2;

        int i = floor(u*height);
        int j = floor(v*width);

        int startPoint = i*3+j*width*3;

        r = (double)image.at(startPoint)/255;
        g = (double)image.at(startPoint+1)/255;
        b = (double)image.at(startPoint+2)/255;
    }

}

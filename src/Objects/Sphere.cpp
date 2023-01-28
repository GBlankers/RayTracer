#include "Sphere.h"

#include <utility>

Sphere::Sphere(const Transformation &t, LightComponents lightComponents, Material material) :
        Shape(t, LightComponents(std::move(lightComponents)), Material(std::move(material))) {}

Collision Sphere::checkCollision(Ray r) {
    double t, t2;
    bool inside;

    if (checkHit(r, t, inside, t2)){
        double red, green, blue;
        this->getColor(r.at(t), red, green, blue);

        LightComponents l = this->lightComponents;
        l.color = new SingleColor(Vec4{red, green, blue, 0});

        return {r, t, calculateNormal(r.at(t), inside), inside, l, this->material, t2};
    }

    return {};
}

bool Sphere::checkHit(Ray r, double &t, bool &inside, double &t2) {
    // Inverse transform the ray
    Matrix4 inverse = getTransformation().getInverse();
    Ray transformedRay = r.transform(inverse);

    if(sqrt(Vec4::dot(transformedRay.getStartPoint(), transformedRay.getStartPoint())) <=1){
        inside = true;
    } else {
        inside = false;
    }

    // Calculate the intersection between the ray and the sphere -> results in 2nd grade function
    double A = Vec4::dot(transformedRay.getDirectionVector(), transformedRay.getDirectionVector());
    double B = Vec4::dot(transformedRay.getStartPoint(), transformedRay.getDirectionVector());
    double C = Vec4::dot(transformedRay.getStartPoint(), transformedRay.getStartPoint()) - 1;
    double D = pow(B, 2) - (A * C);

    if(D < 0) return false;

    double t1 = (-B-sqrt(D))/A;
    double tt = (-B + sqrt(D)) / A;

    if((t1 < tt and t1 > 0) or (t1 > 0 and tt < 0)){
        t = t1;
        t2 = tt;
    } else if((tt < t1 and tt > 0) or (tt > 0 and t1 < 0)){
        t = tt;
        t2 = t1;
    } else {
        t = -1;
        t2 = -1;
    }

    // Discriminant >= 0 -> hit
    return t>0;
}

bool Sphere::checkHit(Ray r, double &t) {
    // Inverse transform the ray
    Matrix4 inverse = getTransformation().getInverse();
    Ray transformedRay = r.transform(inverse);

    // Calculate the intersection between the ray and the sphere -> results in 2nd grade function
    double A = Vec4::dot(transformedRay.getDirectionVector(), transformedRay.getDirectionVector());
    double B = Vec4::dot(transformedRay.getStartPoint(), transformedRay.getDirectionVector());
    double C = Vec4::dot(transformedRay.getStartPoint(), transformedRay.getStartPoint()) - 1;
    double D = pow(B, 2) - (A * C);

    if(D < 0) return false;

    double t1 = (-B-sqrt(D))/A;
    double t2 = (-B+sqrt(D))/A;

    if((t1<t2 and t1>0) or (t1 > 0 and t2 < 0)){
        t = t1;
    } else if((t2<t1 and t2>0) or (t2 > 0 and t1 < 0)){
        t = t2;
    } else {
        t = -1;
    }

    // Discriminant >= 0 -> hit
    return t>0;
}

Vec4 Sphere::calculateNormal(Vec4 hitPoint, bool inside) {
    Vec4 localHit = getTransformation().getInverse() * hitPoint;
    // Calculate normal in local coordinates
    Vec4 normal = inside ? localHit * -1 : localHit;
    normal.setHomogeneous(0);
    // uv-mapping
    double u = 0.5 + (atan2(localHit.getX(), localHit.getZ())/(2*M_PI));
    double v = 0.5 + asin(localHit.getY()*-1)/M_PI;
    // Manipulate normal + transform to world coordinates + normalize
    return Vec4::normalize(t.getForward()*material.manipulateNormal(normal, u, v, hitPoint));
}

void Sphere::getColor(Vec4 hitPoint, double &r, double &g, double &b) {
    // uv-map
    Vec4 localHit = t.getInverse() * hitPoint;
    double u = 0.5 + (atan2(localHit.getX(), localHit.getZ()) / (2 * M_PI));
    double v = 0.5 + asin(localHit.getY() * -1) / M_PI;
    // Get color components
    Vec4 c = lightComponents.color->getColor(u, v, localHit, hitPoint);
    r = c.getX();
    g = c.getY();
    b = c.getZ();
}

SingleColor* Sphere::getBooleanDifferenceColor(Vec4 hitPoint, LightComponents l) {
    // uv-map
    Vec4 localHit = t.getInverse() * hitPoint;
    double u = 0.5 + (atan2(localHit.getX(), localHit.getZ()) / (2 * M_PI));
    double v = 0.5 + asin(localHit.getY() * -1) / M_PI;
    // Get color components
    Vec4 c = l.color->getColor(u, v, localHit, hitPoint);
    return new SingleColor({c.getX(), c.getY(), c.getZ(), 0});
}

#include "Sphere.h"

#include <utility>

Sphere::Sphere(const Transformation &t, LightComponents lightComponents, Material material) :
        Shape(t, LightComponents(std::move(lightComponents)), Material(std::move(material))) {}

Sphere::Sphere(const Transformation &t, const std::string &path, LightComponents lightComponents, Material material) :
        Shape(t, path, LightComponents(std::move(lightComponents)), Material(std::move(material))) {}

Collision Sphere::checkCollision(Ray r) {
    double t;
    bool inside;

    if (checkHit(r, t, inside)){
        double red, green, blue;
        this->getColor(r.at(t), red, green, blue);

        LightComponents l = this->lightComponents;
        l.color = {red, green, blue, 0};

        return {r, t, calculateNormal(r.at(t), inside), inside, l, this->material};
    }

    return {};
}

bool Sphere::checkHit(Ray r, double &t, bool &inside) {
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

bool Sphere::checkHit(Ray r, double &t) {
    // Inverse transform the ray
    Matrix4 inverse = getTransformation().getInverse();
    Ray transformedRay = r.transform(inverse);

    // Calculate the intersection between the ray and the sphere -> results in 2nd grade function
    double A = Vec4::dot(transformedRay.getDirectionVector(), transformedRay.getDirectionVector());
    double B = Vec4::dot(transformedRay.getStartPoint(), transformedRay.getDirectionVector());
    double C = Vec4::dot(transformedRay.getStartPoint(), transformedRay.getStartPoint()) - 1;
    double D = pow(B, 2) - (A * C);

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

bool Sphere::checkHit(Ray r) {
    // Inverse transform the ray
    Matrix4 inverse = getTransformation().getInverse();
    Ray transformedRay = r.transform(inverse);

    // Calculate the intersection between the ray and the sphere -> results in 2nd grade function
    double A = Vec4::dot(transformedRay.getDirectionVector(), transformedRay.getDirectionVector());
    double B = Vec4::dot(transformedRay.getStartPoint(), transformedRay.getDirectionVector());
    double C = Vec4::dot(transformedRay.getStartPoint(), transformedRay.getStartPoint()) - 1;
    double D = pow(B, 2) - (A * C);

    // t >= 0 -> hit
    return (-B-sqrt(D))/A > 0 or (-B+sqrt(D))/A > 0;
}

Vec4 Sphere::calculateNormal(Vec4 hitPoint, bool inside) {
    Vec4 normal(getTransformation().getInverse() * hitPoint);
    normal.setHomogeneous(0);
    // manipulate normal so randomness is less random
    //normal = manipulator.getnormal(normal);

    // If the hit is on the inside of the object the normal needs to be flipped
    if(inside)
        return Vec4::normalize(Vec4::normalize(getTransformation().getForward() * normal) + Vec4::random(-0.3, 0.3) * material.roughness) * -1;

    return Vec4::normalize(Vec4::normalize(getTransformation().getForward() * normal) + Vec4::random(-0.3, 0.3) * material.roughness);
}

void Sphere::getColor(Vec4 hitPoint, double &r, double &g, double &b) {
    if(useColor){
        Shape::getColor(hitPoint, r, g, b);
    } else {
        Vec4 hit = t.getInverse()*hitPoint;
        // uv-map
        double u = 0.5 + (atan2(hit.getX(), hit.getZ())/(2*M_PI));
        double v = 0.5 + asin(hit.getY()*-1)/M_PI;

        int i = floor(u*width);
        int j = floor(v*height);

        int startPoint = i*3+j*width*3;

        r = (double)image.at(startPoint)/255;
        g = (double)image.at(startPoint+1)/255;
        b = (double)image.at(startPoint+2)/255;
    }
}

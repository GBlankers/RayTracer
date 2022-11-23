#include "Sphere.h"

Sphere::Sphere(const Transformation &t, Vec4 color, double ambient, double diffuse, double specular,
               double specularComponent, double reflectivity, double roughness, double transparency, double refractiveIndex) :
        Shape(t, color, ambient, diffuse, specular, specularComponent, reflectivity, roughness, transparency, refractiveIndex) {}

Sphere::Sphere(const Transformation &t, const std::string &path, double ambient, double diffuse, double specular,
               double specularComponent, double reflectivity, double roughness, double transparency,
               double refractiveIndex) :
               Shape(t, path, ambient, diffuse, specular, specularComponent, reflectivity, roughness, transparency, refractiveIndex){}

Collision Sphere::checkCollision(Ray r) {
    double t;
    bool inside;

    if (checkHit(r, t, inside)){
        return {r.at(t), t, Vec4(this->getColor(r.at(t))), Vec4::normalize(calculateNormal(r.at(t), inside) +
        Vec4::random(-0.3, 0.3) * roughness), inside, reflectivity, transparency, refractiveIndex};
    }

    return {};
}

bool Sphere::checkHit(Ray r, double &t, bool &inside) {
    // Inverse transform the ray
    Matrix4 inverse = getT().getInverse();
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
    Matrix4 inverse = getT().getInverse();
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
    Matrix4 inverse = getT().getInverse();
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
    Vec4 normal(getT().getInverse()*hitPoint);
    normal.setHomogeneous(0);
    // manipulate normal so randomness is less random
    //normal = manipulator.getnormal(normal);

    // If the hit is on the inside of the object the normal needs to be flipped
    if(inside)
        return Vec4::normalize(getT().getForward()*normal)*-1;

    return Vec4::normalize(getT().getForward()*normal);
}

const Vec4 &Sphere::getColor(Vec4 hitPoint) const {
    if(useColor)
        return color;

    Vec4 hit = t.getInverse()*hitPoint;
    // uv-map
    double u = 0.5 + (atan2(hit.getZ(), hit.getX())/(2*M_PI));
    double v = 0.5 + asin(hit.getY())/M_PI;

    int i = floor(u*width);
    int j = floor(v*height);

    int startPoint = i*3+j*3;

    Vec4 imageColor((double)image[startPoint]/255, (double)image[startPoint+1]/255, (double)image[startPoint+2]/255, 0);

    // get color at that point
    return imageColor;
}

#ifndef RAYTRACER_CUBE_H
#define RAYTRACER_CUBE_H

#include "Shape.h"

class Cube : public Shape{
public:
    explicit Cube(const Transformation &t, Vec4 color, double ambient, double diffuse, double specular, double specularComponent,
                  double reflectivity, double roughness, double transparency, double refractiveIndex);

    Collision checkCollision(Ray r) override;

    bool checkHit(Ray r, double &t, bool &inside) override;
    bool checkHit(Ray r, double &t) override;
    bool checkHit(Ray r) override;
    Vec4 calculateNormal(Vec4 hitPoint, bool inside) override;

    static bool checkInCube(Ray r, double t);
};


#endif //RAYTRACER_CUBE_H

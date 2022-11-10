#ifndef RAYTRACER_PLANE_H
#define RAYTRACER_PLANE_H

#include "Shape.h"
#include "LightSource.h"

class Plane : public Shape{
private:
    bool checkerBoard = false;
    int checkerBoardSize = 800;
public:
    explicit Plane(const Transformation &t, Vec4 color, double ambient, double diffuse, double specular,
                   double specularComponent, double reflectivity, double roughness);

    Collision checkCollision(Ray r) override;

    bool checkHit(Ray r, double &t) override;
    bool checkHit(Ray r) override;
    Vec4 calculateNormal(Vec4 hitPoint) override;

    void setCheckerBoardPattern(bool b, int size);
};


#endif //RAYTRACER_PLANE_H

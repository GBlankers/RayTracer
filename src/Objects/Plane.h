#ifndef RAYTRACER_PLANE_H
#define RAYTRACER_PLANE_H

#include "Shape.h"
#include "LightSource.h"

class Plane : public Shape{
private:
    bool checkerBoard = false;
    int checkerBoardSize = 800;
    double planeLength = -1, planeWidth = -1;
public:
    explicit Plane(const Transformation &t, Vec4 color, double ambient, double diffuse, double specular,
                   double specularComponent, double reflectivity, double roughness, double transparency, double refractiveIndex);
    explicit Plane(const Transformation &t, const std::string& path , double ambient, double diffuse, double specular,
                   double specularComponent, double reflectivity, double roughness, double transparency, double refractiveIndex);

    Collision checkCollision(Ray r) override;

    bool checkHit(Ray r, double &t, bool &inside) override;
    bool checkHit(Ray r, double &t) override;
    bool checkHit(Ray r) override;
    Vec4 calculateNormal(Vec4 hitPoint, bool inside) override;

    void setCheckerBoardPattern(bool b, int size);
    void setSize(double l, double w);

    void getColor(Vec4 hitPoint, double &r, double &g, double &b) override;
};


#endif //RAYTRACER_PLANE_H

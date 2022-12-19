#ifndef RAYTRACER_PLANE_H
#define RAYTRACER_PLANE_H

#include "Shape.h"
#include "LightSource.h"

class Plane : public Shape{
private:
    bool checkerBoard = false;
    int checkerBoardSize = 800;
public:
    explicit Plane(const Transformation &t, LightComponents lightComponents, Material material);
    explicit Plane(const Transformation &t, const std::string& path, LightComponents lightComponents, Material material);

    Collision checkCollision(Ray r) override;
    bool checkHit(Ray r, double &t, bool &inside) override;
    bool checkHit(Ray r, double &t) override;

    Vec4 calculateNormal(Vec4 hitPoint, bool inside) override;

    void setCheckerBoardPattern(bool b, int size);

    void getColor(Vec4 hitPoint, double &r, double &g, double &b) override;
};


#endif //RAYTRACER_PLANE_H

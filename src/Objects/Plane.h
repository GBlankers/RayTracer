#ifndef RAYTRACER_PLANE_H
#define RAYTRACER_PLANE_H

#include "Shape.h"
#include "LightSource.h"

class Plane : public Shape{
private:
    bool checkerBoard = false;
public:
    explicit Plane(const Transformation &t, Vec4 color);

    Collision checkCollision(Ray r, std::vector<std::shared_ptr<LightSource>> l, std::vector<std::shared_ptr<Shape>> worldObjects) override;
    Vec4 getIntensityCorrectedColor(Vec4 hit, double intensity) override;
    Vec4 calculateNormal(Vec4 hitPoint) override;
    bool checkHit(Ray r) override;

    void setCheckerBoardPattern(bool b);
};


#endif //RAYTRACER_PLANE_H

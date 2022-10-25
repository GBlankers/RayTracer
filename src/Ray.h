#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include "Math/Vec4.h"
#include "Math/Matrix4.h"

class Ray {
private:
    Vec4 startPoint; // Starting point
    Vec4 directionVector{}; // Direction
    Vec4 screenVector; // Vector pointing to the screen
    Vec4 upVector; // To define the near plane
    Vec4 crossVector{}; // Define the vector cross to the up and direction vector
public:
    Ray(Vec4 start, Vec4 direction);
    Ray(Vec4 start, Vec4 screenVector, Vec4 upVector);

    Ray(const Vec4 &startPoint, const Vec4 &directionVector, const Vec4 &screenVector, const Vec4 &upVector);

    Ray transform(Matrix4 trans);
    Vec4 at(double t) const;

    void setStartPoint(const Vec4 &startPoint);
    void setDirectionVector(const Vec4 &directionVector);
    void setPixel(int distance, int width, int height);
    const Vec4 &getStartPoint() const;
    const Vec4 &getDirectionVector() const;
};

#endif //RAYTRACER_RAY_H

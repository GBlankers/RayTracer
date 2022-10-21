#ifndef RAYTRACER_TRANSFORMATION_H
#define RAYTRACER_TRANSFORMATION_H

#include "Math/Vec4.h"
#include "Math/Matrix4.h"

class Transformation {
private:
    Matrix4 forward;
    Matrix4 inverse;
    bool firstTransformation = true;
public:
    explicit Transformation() = default;
    void addTranslation(double x, double y, double z);
    void addScaling(double sx, double sy, double sz);
    void addRotationX(double thetaX);
    void addRotationY(double thetaY);
    void addRotationZ(double thetaZ);
    const Matrix4 &getForward() const;
    const Matrix4 &getInverse() const;
};


#endif //RAYTRACER_TRANSFORMATION_H

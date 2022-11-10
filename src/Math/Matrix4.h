#ifndef RAYTRACER_MATRIX4_H
#define RAYTRACER_MATRIX4_H

#include "Vec4.h"
#include <cmath>

class Matrix4 {
public:
    double matrix[4][4] = {{1,0,0,0},{0,1,0,0},
                           {0,0,1,0}, {0,0,0,1}};
    // Constructors
    explicit Matrix4() = default;
    explicit Matrix4(double (*matrix)[4]);
    // Add transformations
    void addTranslation(double x, double y, double z);
    void addScaling(double Sx, double Sy, double Sz);
    void addRotationX(double thetaX);
    void addRotationY(double thetaY);
    void addRotationZ(double thetaZ);
    // Operator overloading
    bool operator==(const Matrix4 &rhs) const;
    Vec4 operator*(Vec4 vectorToTransform) const;
    Matrix4 operator*(Matrix4 otherMatrix) const;
};


#endif //RAYTRACER_MATRIX4_H

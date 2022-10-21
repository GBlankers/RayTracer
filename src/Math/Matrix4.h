#ifndef RAYTRACER_MATRIX4_H
#define RAYTRACER_MATRIX4_H

#include "Vec4.h"

class Matrix4 {
public:
    double matrix[4][4] = {{0,0,0,0},{0,0,0,0},
                           {0,0,0,0}, {0,0,0,0}};
    // Constructors
    explicit Matrix4() = default;
    explicit Matrix4(double (*matrix)[4]);
    // Add transformations
    void addTranslation(double x, double y, double z);
    void addScaling(double Sx, double Sy, double Sz);
    // Operator overloading
    bool operator==(const Matrix4 &rhs) const;
    Vec4 operator*(Vec4 vectorToTransform) const;
    Matrix4 operator*(Matrix4 otherMatrix) const;
};


#endif //RAYTRACER_MATRIX4_H

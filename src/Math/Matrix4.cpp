#include "Matrix4.h"

void Matrix4::addTranslation(double x, double y, double z) {
    for(int i = 0; i<4; i++){
        matrix[i][i] = 1.0;
    }
    matrix[0][3] = x;
    matrix[1][3] = y;
    matrix[2][3] = z;
}

void Matrix4::addScaling(double Sx, double Sy, double Sz) {
    matrix[0][0] = Sx;
    matrix[1][1] = Sy;
    matrix[2][2] = Sz;
    matrix[3][3] = 1;
}

Vec4 Matrix4::operator*(Vec4 vectorToTransform) const {
    double vector[4] = {vectorToTransform.getX(), vectorToTransform.getY(), vectorToTransform.getZ(), (double)vectorToTransform.getHomogeneous()};
    double transformed[4];
    double temp;
    for(int i = 0; i<4; i++){
        temp = 0.0;
        for(int j = 0; j<4;j++){
            temp += vector[i]*matrix[i][j];
        }
        transformed[i] = temp;
    }
    return {transformed[0], transformed[1], transformed[2], (int)transformed[3]};
}

Matrix4 Matrix4::operator*(Matrix4 otherMatrix) const {
    double multi[4][4] = {{0,0,0,0}, {0,0,0,0}, {0,0,0,0},
                          {0,0,0,0}};
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
            for(int k = 0; k < 4; ++k)
            {
                multi[i][j] += this->matrix[i][k] * otherMatrix.matrix[k][j];
            }
    return Matrix4(multi);
}

Matrix4::Matrix4(double (*newMatrix)[4]){
    for(int i = 0; i<4; i++){
        for(int j = 0; j<4; j++){
            matrix[i][j] = newMatrix[i][j];
        }
    }
}


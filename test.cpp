#include <cassert>

#include "src/Math/Matrix4.h"
#include "src/Math/Vec4.h"

void testVectorMatrixMulti(){
    double inputMatrix[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8},
                                {0, 0, 0, 0}, {4, 3, 2, 1}};

    Matrix4 testMatrix(inputMatrix);

    Vec4 testVector(2, 4, 6, 8);
    Vec4 result = testMatrix*testVector;

    Vec4 expected(60, 140, 0, 40);

    assert(expected == result);
}

void testMatrixMatrixMulti(){
    double inputMatrix[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8},
                                {0, 0, 0, 0}, {4, 3, 2, 1}};
    double inputMatrix2[4][4] = {{2, 4, 6, 8}, {1, 3, 5, 7},
                                 {1, 4, 8, 2},{5, 3, 7, 9}};

    Matrix4 mat1(inputMatrix);
    Matrix4 mat2(inputMatrix2);

    Matrix4 multi1 = mat1*mat2;
    Matrix4 multi2 = mat2*mat1;

    double expectedMatrix1[4][4] = {{27, 34, 68, 64}, {63, 90, 172, 168},
                                    {0, 0, 0, 0}, {18, 36, 62, 66}};
    double expectedMatrix2[4][4] = {{54, 52, 50 ,48}, {44, 41, 38, 35},
                                    {29, 32, 35, 38}, {56, 55, 54, 53}};

    Matrix4 expected1(expectedMatrix1);
    Matrix4 expected2(expectedMatrix2);

    assert(multi1==expected1);
    assert(multi2==expected2);
}

void testCrossProduct(){
    Vec4 vec1(1, 0, 0, 0);
    Vec4 vec2(0, 1, 0, 0);

    Vec4 result;
    Vec4 expected(0, 0, 1, 0);

    result = Vec4::cross(vec1, vec2);
    assert(result==expected);
}

int main(){
    testVectorMatrixMulti();
    testMatrixMatrixMulti();
    testCrossProduct();
    return 0;
}
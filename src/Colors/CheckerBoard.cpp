#include "CheckerBoard.h"

CheckerBoard::CheckerBoard(Vec4 c1, Vec4 c2, double size) {
    assert(c1.getX()>=0 && c1.getX()<=1.0);
    assert(c1.getY()>=0 && c1.getY()<=1.0);
    assert(c1.getZ()>=0 && c1.getZ()<=1.0);
    assert(c2.getX()>=0 && c2.getX()<=1.0);
    assert(c2.getY()>=0 && c2.getY()<=1.0);
    assert(c2.getZ()>=0 && c2.getZ()<=1.0);
    this->color1 = c1;
    this->color2 = c2;
    this->checkerBoardSize = size;
}

Vec4 CheckerBoard::getColor(double u, double v, Vec4 localHit, Vec4 worldHit) {
    int A = 100; // shift pattern to not get origin weirdness

    if(((int) (A + u / checkerBoardSize) + (int) (A + v / checkerBoardSize)) % 2){
        return color1;
    }
    return color2;
}

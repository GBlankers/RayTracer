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

Vec4 CheckerBoard::getColor(const std::string &objectType, double u, double v, Vec4 localHit, Vec4 worldHit) {
    int A = 100; // shift pattern to not get origin weirdness
    bool check = true;

    // for every object the pattern need to be calculated differently to avoid strange patterns
    if(objectType == "plane"){
        check = ((int)(A+localHit.getX()/checkerBoardSize)+(int)(A+localHit.getZ()/checkerBoardSize))%2;
    } else if(objectType == "sphere"){
        check = ((int)(A+u/checkerBoardSize)+(int)(A+v/checkerBoardSize))%2;
    } else if(objectType == "cube"){
        if(localHit.getZ() <= (-1+EPSILON) or localHit.getZ() >= (1-EPSILON)){
            check = ((int)(A+localHit.getX()/checkerBoardSize)+(int)(A+localHit.getY()/checkerBoardSize))%2;
        } else if(localHit.getY() <= (-1+EPSILON) or localHit.getY() >= (1-EPSILON)){
            check = ((int)(A+localHit.getX()/checkerBoardSize)+(int)(A+localHit.getZ()/checkerBoardSize))%2;
        } else if(localHit.getX() <= (-1+EPSILON) or localHit.getX() >= (1-EPSILON)){
            check = ((int)(A+localHit.getY()/checkerBoardSize)+(int)(A+localHit.getZ()/checkerBoardSize))%2;
        }
    }

    if(check){
        return color1;
    }
    return color2;
}

Vec4 CheckerBoard::getColor() {
    return color1;
}

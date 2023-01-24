#include "Marble.h"

Vec4 Marble::getColor(double u, double v, Vec4 localHit, Vec4 worldHit) {
    Vec4 startColor = {0.7, 0.7, 0.7, 0};
    double A = 8;
    double c = undulate(sin(M_2_PI*localHit.getZ() + A * n.turbulate(9, localHit)));
    return {startColor.getX()+c*(1-startColor.getX()),
            startColor.getY()+c*(1-startColor.getY()),
            startColor.getZ()+c*(1-startColor.getZ()), 0};
}

double Marble::undulate(double x) {
    return 2*sin(x)+cos(3*x);
}

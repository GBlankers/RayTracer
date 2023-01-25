#include "Marble.h"

Vec4 Marble::getColor(double u, double v, Vec4 localHit, Vec4 worldHit) {
    Vec4 startColor = {0.2, 0.2, 0.2, 0};
    double A = 3;
    float scale = 4;
    double temp = undulate(sin(M_2_PI * localHit.getY() + A * n.turbulate(scale, localHit)));
    return {startColor.getX() + temp * (1 - startColor.getX()),
            startColor.getY() + temp * (1 - startColor.getY()),
            startColor.getZ() + temp * (1 - startColor.getZ()), 0};
}

double Marble::undulate(double x) {
    return 2*sin(x/4);
}

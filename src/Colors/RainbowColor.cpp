#include "RainbowColor.h"

Vec4 RainbowColor::getColor(double u, double v, Vec4 localHit, Vec4 worldHit) {
    double intensity = sqrt(pow(u, 2)+ pow(v, 2))/ sqrt(2);
    double theta = atan(u/v);

    double b = (theta-M_PI_4)/M_PI_4;

    return {u, (1-fabs(b)), v, 0};
}

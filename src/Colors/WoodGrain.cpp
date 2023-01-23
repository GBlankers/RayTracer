#include "WoodGrain.h"

Vec4 WoodGrain::getColor(double u, double v, Vec4 localHit, Vec4 worldHit) {
    double r = sqrt(pow(u,2)+pow(v, 2));
    double K = 5, N = 0.6, B = 2;
    double temp = r+K*sin((asin(localHit.getY())/N)+B*localHit.getY());
    int rings = ((int)(temp))%2;



    // Darker brown
    Vec4 color1 = {164.0/256, 116.0/256, 73.0/256, 0};
    // Lighter brown
    Vec4 color2 = {(226-164)*1.0/256, (187-116)*1.0/256, (123-73)*1.0/256, 0};

    return color1 + color2 * (rings%2);
}

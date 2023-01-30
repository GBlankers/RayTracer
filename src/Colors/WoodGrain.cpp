#include "WoodGrain.h"

Vec4 WoodGrain::getColor(double u, double v, Vec4 localHit, Vec4 worldHit) {
    double r = sqrt(pow(worldHit.getX(),2)+pow(worldHit.getZ(), 2));
    double temp = (r/M)+K*sin((asin(localHit.getY())/N)+B*worldHit.getY());
    int rings = ((int)(temp))%2;

    // Darker brown
    Vec4 color1 = {164.0/256, 116.0/256, 73.0/256, 0};
    // Lighter brown
    Vec4 color2 = {(226-164)*1.0/256, (187-116)*1.0/256, (123-73)*1.0/256, 0};

    return color1 + color2 * (rings%2);
}

WoodGrain::WoodGrain(double M, double K, double N, double B): M(M), K(K), N(N), B(B) {}

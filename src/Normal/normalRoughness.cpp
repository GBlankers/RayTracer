#include "normalRoughness.h"

Vec4 normalRoughness::manipulateNormal(Vec4 normal, double roughness, double u, double v, Vec4 worldHit) {
    double dx, dy, dz;
    double scale = 5;
    // Default random noise using hashes and the roughness param
    // dividing the hash by the max/2 value gives a return between 0 and 2 -> -1 -> between -1 and 1;
    // divide by 'scale' to get a smaller range and make the displacement of the vector smaller
    dx = (((double)doubleHash(worldHit.getX()+worldHit.getY()+worldHit.getZ())/((double)std::numeric_limits<size_t>::max()/2.0))-1)/scale;
    dy = (((double)doubleHash(worldHit.getX()-worldHit.getY()+worldHit.getZ())/((double)std::numeric_limits<size_t>::max()/2.0))-1)/scale;
    dz = (((double)doubleHash(worldHit.getX()+worldHit.getZ()-worldHit.getX())/((double)std::numeric_limits<size_t>::max()/2.0))-1)/scale;

    return normal + Vec4{dx, dy, dz, 0}*roughness;
}

#ifndef RAYTRACER_NOISE_H
#define RAYTRACER_NOISE_H

#include <cstdlib>
#include "Vec4.h"

#define PERM(x) index[(x)&255]
#define INDEX(ix, iy, iz) PERM(ix + PERM(iy + PERM(iz)))
#define linearInterpolation(F, A, B) A+F*(B-A)

/**
 * Noise class used for marble. Implementation from the ray tracing book
 */
class Noise {
private:
    float* noiseTable;
    unsigned char* index;
    float latticeNoise(int i, int y, int z);
public:
    Noise();
    float noise(float scale, Vec4 point);
    double turbulate(float scale, Vec4 point);
};


#endif //RAYTRACER_NOISE_H

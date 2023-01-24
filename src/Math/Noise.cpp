#include "Noise.h"

Noise::Noise() {
    int i;
    index = new unsigned char[256];
    for(i = 0; i<256; i++) index[i] = i; // fill array with indices. Cannot be done with random as we could not be sure
    // that all the indices will be present in the array.
    for(i = 0; i<256; i++){ // Swap indices for randomness
        int which = rand() % 256;
        unsigned char temp = index[which];
        index[which] = index[i];
        index[i] = temp;
    }
    noiseTable = new float[256];
    for(i = 0; i<256; i++) noiseTable[i] = (float)randomDouble(0, 1);
}

float Noise::latticeNoise(int i, int y, int z) {
    return noiseTable[INDEX(i, y, z)];
}

float Noise::noise(float scale, Vec4 point) {
    float d[2][2][2];
    Vec4 tempPoint{point.getX()*scale+100000,
                   point.getY()*scale+100000,
                   point.getZ()*scale+100000,1};

    int ix = (int) tempPoint.getX(), iy = (int) tempPoint.getY(), iz = (int) tempPoint.getZ();
    double tx, ty, tz, x0, x1, x2, x3, y0, y1;
    tx = tempPoint.getX() - ix; ty = tempPoint.getY() - iy; tz = tempPoint.getZ() - iz;
    //double mtx = 1.0-tx, mty = 1.0-ty, mtz = 1.0-tz;

    for(int k = 0; k <= 1; k++){
        for(int j = 0; j <= 1; j++){
            for(int i = 0; i <= 1; i++){
                d[k][j][i] = latticeNoise(ix + i, iy + j, iz + k);
            }
        }
    }

    x0 = linearInterpolation(tx, d[0][0][0],d[0][0][1]);
    x1 = linearInterpolation(tx, d[0][1][0],d[0][1][1]);
    x2 = linearInterpolation(tx, d[1][0][0],d[1][0][1]);
    x3 = linearInterpolation(tx, d[1][1][0],d[1][1][1]);
    y0 = linearInterpolation(ty, x0, x1);
    y1 = linearInterpolation(ty, x2, x3);
    return linearInterpolation(tz, y0, y1);
}

double Noise::turbulate(float scale, Vec4 point) {
    return (1.0/2)*noise(scale, point)+(1.0/4)*noise(2*scale, point)+(1.0/8)*noise(4*scale, point);
}

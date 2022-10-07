#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

class Ray {
private:
    double x,y,z; // Starting point
    double vx,vy,vz; // Direction
    int reflectionNr; // How many reflections have been made
public:
    Ray(int x, int y, int z, double vx, double vy, double vz, int reflectionNr);
    Ray(int x, int y, int z, double vx, double vy, double vz);

    double getX() const;

    double getY() const;

    double getZ() const;

    double getVx() const;

    double getVy() const;

    double getVz() const;
};

#endif //RAYTRACER_RAY_H

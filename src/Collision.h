#ifndef RAYTRACER_COLLISION_H
#define RAYTRACER_COLLISION_H

class Collision {
private:
    double x,y,z; // location of the collision
    double t; // time of the collision to determine the place at the ray
    double r, g, b; // color of the shape where this collision has happened

public:
    Collision(double x, double y, double z, double t, double r, double g, double b);
};

#endif //RAYTRACER_COLLISION_H

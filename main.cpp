#include <iostream>

#include "src/Sphere.h"
#include "src/Ray.h"
#include "src/Transformation.h"
#include "src/Collision.h"

int main() {

    trans t{};
    t.translation = Vec3(0, 0, 0);

    Transformation transformationSphere(t);

    Sphere newSphere(transformationSphere);

    Ray eyeRay(Vec3(10, 10, 10), Vec3(-1, -1, -1));

    Collision c = newSphere.checkCollision(eyeRay);

    return 0;
}

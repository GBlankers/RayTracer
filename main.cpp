#include <iostream>

#include "src/Sphere.h"
#include "src/Ray.h"
#include "src/Transformation.h"
#include "src/Collision.h"

int main() {

    trans t{};
    t.translationX = 0;
    t.translationY = 0;
    t.translationZ = 0;

    Transformation transformationSphere(t);

    Sphere newSphere(transformationSphere);

    Ray eyeRay(10, 10, 10, -1, -1, -1);

    Collision c = newSphere.checkCollision(eyeRay);


    return 0;
}

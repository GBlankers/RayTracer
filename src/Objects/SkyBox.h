#ifndef RAYTRACER_SKYBOX_H
#define RAYTRACER_SKYBOX_H

#include "../Math/Vec4.h"
#include "../Colors/Color.h"
#include "../Colors/SingleColor.h"
#include <utility>

class SkyBox {
private:
    Color* c = new SingleColor(Vec4(0.53, 0.81, 0.92, 1));
public:
    explicit SkyBox();
    explicit SkyBox(Color* color);

    Vec4 getColor(Vec4 direction);
};


#endif //RAYTRACER_SKYBOX_H

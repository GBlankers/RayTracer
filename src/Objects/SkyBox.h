#ifndef RAYTRACER_SKYBOX_H
#define RAYTRACER_SKYBOX_H


#include "../Math/Vec4.h"

class SkyBox {
private:
    Vec4 color = {0.53, 0.81, 0.92, 1};
    std::string path;
    bool useColor = false;
public:
    explicit SkyBox();
    explicit SkyBox(Vec4 color);
    explicit SkyBox(std::string path);

    Vec4 getColor(Vec4 direction) const;
};


#endif //RAYTRACER_SKYBOX_H

#ifndef RAYTRACER_SKYBOX_H
#define RAYTRACER_SKYBOX_H

#include "../Math/Vec4.h"
#include "../Colors/Color.h"
#include "../Colors/SingleColor.h"
#include <utility>

/**
 * Sky box, the color a pixel will get when there are no objects hit
 */
class SkyBox {
private:
    /**
     * Default color
     */
    Color* c = new SingleColor(Vec4(0.53, 0.81, 0.92, 1));
public:
    /**
     * Default constructor that uses the default color
     */
    explicit SkyBox();

    /**
     * Skybox constructor, give a color to the sky
     * @param color the color the sky
     */
    explicit SkyBox(Color* color);

    /**
     * get the color of the sky given a ray direction
     * @param direction the color of the ray that hasn't hit any objects
     * @return the color of the sky
     */
    Vec4 getColor(Vec4 direction) const;
};


#endif //RAYTRACER_SKYBOX_H

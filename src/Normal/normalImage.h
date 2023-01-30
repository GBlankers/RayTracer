#ifndef RAYTRACER_NORMALIMAGE_H
#define RAYTRACER_NORMALIMAGE_H

#include "normalManipulator.h"
#include "../../include/code/lodepng.h"

/**
 * Normal mapping class. Using an image, the normal of an object will be changed
 */
class normalImage : public normalManipulator{
private:
    /**
     * Vector with the image information
     */
    std::vector<unsigned char> normalMap;
    /**
     * Width and height of the image
     */
    unsigned width = 0, height = 0;
public:
    explicit normalImage(const std::string& path);
    Vec4 manipulateNormal(Vec4 normal, double roughness, double u, double v, Vec4 worldHit) override;
};


#endif //RAYTRACER_NORMALIMAGE_H

#ifndef RAYTRACER_IMAGECOLOR_H
#define RAYTRACER_IMAGECOLOR_H

#include "Color.h"
#include "../settings.h"
#include "../../include/code/lodepng.h"

/**
 * Solid texture to give color to an object using an image
 */
class ImageColor : public Color{
private:
    /**
     * When a picture cannot be found, use a default red color
     */
    Vec4 defaultColor = {1, 0, 0, 0};
    /**
     * Vector with all the image pixel information
     */
    std::vector<unsigned char> image;
    /**
     * width and height of the image
     */
    unsigned width=0, height=0;
public:
    /**
     * Constructor for the imageColor class. An image will be used to color an object
     * @param path the path to the image
     */
    explicit ImageColor(const std::string& path);
    Vec4 getColor(double u, double v, Vec4 localHit, Vec4 worldHit) override;
};


#endif //RAYTRACER_IMAGECOLOR_H

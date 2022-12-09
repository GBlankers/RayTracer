#ifndef RAYTRACER_IMAGECOLOR_H
#define RAYTRACER_IMAGECOLOR_H

#include "Color.h"
#include "../../include/code/lodepng.h"

class ImageColor : public Color{
private:
    Vec4 defaultColor = {1, 0, 0, 0};
    std::vector<unsigned char> image;
    unsigned width=0, height=0;
public:
    explicit ImageColor(const std::string& path);
    Vec4 getColor(const std::string &objectType, double u, double v) override;

    Vec4 getColor() override;
};


#endif //RAYTRACER_IMAGECOLOR_H

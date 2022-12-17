#include "ImageColor.h"

ImageColor::ImageColor(const std::string& path) {
    unsigned error = lodepng::decode(image, width, height, path, LCT_RGB);
    if(error) {
        printf("error %u: %s\nDefault color will be used", error, lodepng_error_text(error));
    }
}

Vec4 ImageColor::getColor(const std::string &objectType, double u, double v, Vec4 localHit, Vec4 worldHit) {
    if(image.empty())
        return defaultColor;

    int i = 0, j = 0;

    if(objectType == "sphere"){
        i = floor(u * width);
        j = floor(v * height);
    } else if(objectType == "plane"){
        i = floor(fmod(u, height));
        j = floor(fmod(v, width));
    }

    int startPoint = i * 3 + j * width * 3;

    double r = (double)image[startPoint]/255;
    double g = (double)image[startPoint+1]/255;
    double b = (double)image[startPoint+2]/255;

    // get color at that point
    return {r, g, b, 0};
}

Vec4 ImageColor::getColor() {
    return defaultColor;
}

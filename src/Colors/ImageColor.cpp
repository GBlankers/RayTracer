#include "ImageColor.h"

ImageColor::ImageColor(const std::string& path) {
    unsigned error = lodepng::decode(image, width, height, path, LCT_RGB);
    if(error) {
        printf("error %u: %s\nDefault color will be used", error, lodepng_error_text(error));
    }
}

Vec4 ImageColor::getColor(double u, double v, Vec4 localHit, Vec4 worldHit) {
    if(image.empty())
        return defaultColor;

    int i = floor(u * width);
    int j = floor(v * height);

    int startPoint = i * 3 + j * width * 3;

    double r = (double)image[startPoint]/255;
    double g = (double)image[startPoint+1]/255;
    double b = (double)image[startPoint+2]/255;

    // get color at that point
    return {r, g, b, 0};
}

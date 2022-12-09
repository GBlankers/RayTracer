#include "ImageColor.h"

ImageColor::ImageColor(const std::string& path) {
    unsigned error = lodepng::decode(image, width, height, path, LCT_RGB);
    if(error) {
        printf("error %u: %s\nDefault color will be used", error, lodepng_error_text(error));
    }
}

Vec4 ImageColor::getColor(const std::string &objectName, Vec4 direction) {
    if(image.empty())
        return defaultColor;

    if(objectName == "sphere"){
        // uv-map
        double u = 0.5 + (atan2(direction.getZ(), direction.getX())/(2*M_PI));
        double v = 0.5 + asin(direction.getY()*-1)/M_PI;

        int i = floor(u*width);
        int j = floor(v*height);

        int startPoint = i*3+j*width*3;

        double r = (double)image[startPoint]/255;
        double g = (double)image[startPoint+1]/255;
        double b = (double)image[startPoint+2]/255;

        // get color at that point
        return {r, g, b, 0};
    }


    return defaultColor;
}

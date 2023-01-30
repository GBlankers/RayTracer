#include "ImageColor.h"

ImageColor::ImageColor(const std::string& path) {
    // Load the image using the lodepng package (included in the \include\code folder)
    unsigned error = lodepng::decode(image, width, height, path, LCT_RGB);
    if(error) {
        printf("error %u: %s\nDefault color will be used", error, lodepng_error_text(error));
    }
}

Vec4 ImageColor::getColor(double u, double v, Vec4 localHit, Vec4 worldHit) {
    // Image couldn't be read
    if(image.empty())
        return defaultColor;

    // using uv-mapping, calculate the indices for the image pixels
    int i = floor(u * width);
    int j = floor(v * height);

    // The image is stored in a 1D vector -> calculate the index in this vector
    int startPoint = i * 3 + j * width * 3;

    // Calculate the color
    double r = (double)image[startPoint]/255;
    double g = (double)image[startPoint+1]/255;
    double b = (double)image[startPoint+2]/255;

    // get color at that point
    return {r, g, b, 0};
}

#include "normalImage.h"

normalImage::normalImage(const std::string& path) {
    if(!path.empty()){
        unsigned error = lodepng::decode(normalMap, width, height, path, LCT_RGB);
        if(error) {
            printf("error %u: %s\nNo normal map will be used", error, lodepng_error_text(error));
        }
    }
}

Vec4 normalImage::manipulateNormal(Vec4 normal, double roughness, double u, double v, Vec4 worldHit) {
    double dx, dy, dz;
    if(normalMap.empty()){
        return normal;
    }
    // scale uv to image dimensions
    int i = floor(u*height);
    int j = floor(v*width);
    // Calculate the point in the array
    int startPoint = i*3+j*width*3;
    // Get the individual pixel values + scaling
    dx = ((double)normalMap.at(startPoint)*2/255)-1; // x-displacement is mapped to the red color
    dz = ((double)normalMap.at(startPoint+1)*2/255)-1; // z-displacement is mapped to the green color
    dy = ((double)normalMap.at(startPoint+2)/255); // y-displacement is mapped to the blue color
    // Return the normalized vector
    return Vec4::normalize(Vec4{dx, dy, dz, 0});
}

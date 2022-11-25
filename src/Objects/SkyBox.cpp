#include "SkyBox.h"



SkyBox::SkyBox() = default;

SkyBox::SkyBox(Vec4 color) {
    this->color=color;
    this->useColor=true;
    this->path="";
}

SkyBox::SkyBox(const std::string& path) : path(path){
    this->useColor=false;
    this->color={0, 0, 0, 0};

    unsigned error = lodepng::decode(image, width, height, path, LCT_RGB);
    if(error) {
        printf("error %u: %s\nDefault color will be used", error, lodepng_error_text(error));
        this->useColor = true;
    }

}

Vec4 SkyBox::getColor(Vec4 direction) const{
    if(useColor)
        return color;

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

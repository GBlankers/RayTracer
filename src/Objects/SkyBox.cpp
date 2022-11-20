#include "SkyBox.h"

#include <utility>

SkyBox::SkyBox() = default;

SkyBox::SkyBox(Vec4 color) {
    this->color=color;
    this->useColor=true;
    this->path="";
}

SkyBox::SkyBox(std::string path) : path(std::move(path)){
    this->useColor=false;
    this->color={0, 0, 0, 0};
}

Vec4 SkyBox::getColor(Vec4 direction) const{
    if(useColor)
        return color;
    else
        return color;
}

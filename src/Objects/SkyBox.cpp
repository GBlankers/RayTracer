#include "SkyBox.h"

SkyBox::SkyBox() = default;

SkyBox::SkyBox(Color* color) {
    this->c = color;
}

Vec4 SkyBox::getColor(Vec4 direction){
    return c->getColor("sphere", direction);
}

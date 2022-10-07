#ifndef RAYTRACER_TRANSFORMATION_H
#define RAYTRACER_TRANSFORMATION_H
struct trans{
    double translationX, translationY, translationZ;
    //double scaleX, scaleY, scaleZ;
    //double rotationX, rotationY, rotationZ;
};

class Transformation {
private:
    trans forwardTransformation{};
    trans inverseTransformation{};
public:
    explicit Transformation(trans forwardTransformation);

    Transformation();

    void calculateInverseTransformation();

    const trans &getInverseTransformation() const;
    const trans &getForwardTransformation() const;
};


#endif //RAYTRACER_TRANSFORMATION_H

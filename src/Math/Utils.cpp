#include "Utils.h"

double randomDouble(){
    static std::uniform_real_distribution<double> distribution(-1.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

double randomDouble(double min, double max){
    double f = (double)rand() / RAND_MAX;
    return min + f * (max - min);

}
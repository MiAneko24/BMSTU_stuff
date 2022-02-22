#include "point.hpp"


Point::Point(double x, double y, double z): pX(x), pY(y), pZ(z) {};

double Point::getX() const {
    return pX;
}

double Point::getY() const {
    return pY;
}

double Point::getZ() const {
    return pZ;
}

void Point::transform(const Matrix<double> &transform_matrix)
{
    Vector<double> result(4);
    Vector<double> point = toVector();
    result = point * transform_matrix;

    setFromVector(result);
}

Vector<double> Point::toVector()
{
    Vector<double> result(4);
    result[0] = pX;
    result[1] = pY;
    result[2] = pZ;
    result[3] = 1;

    return result;    
}

void Point::setFromVector(Vector<double> &vector)
{
    pX = vector[0];
    pY = vector[1];
    pZ = vector[2];
}
#include "point.hpp"

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
    pX = vector[1];
    pX = vector[2];
}
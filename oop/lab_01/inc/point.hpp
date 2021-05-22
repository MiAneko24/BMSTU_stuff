#ifndef POINT_HPP
#define POINT_HPP
#include "vector.hpp"
#include <memory>
#define DIMENSION 3

class Point {
    public:
        Point() = default;
        Point(double x, double y, double z): pX(x), pY(y), pZ(z) {};
        Point(const Point &) = default;
        Point(const Vector<double> vector); //?
        Point &operator =(const Point&) = default;
        
        void transform(const Matrix<double> &transform_matrix);
        
        double getX() const {
            return pX;
        }
        double getY() const {
            return pY;
        }
        double getZ() const {
            return pZ;
        }
        Vector<double> toVector();
        void setFromVector(Vector<double> &vector);

    private:
        double pX;
        double pY;
        double pZ;
};

//убрать потом в cpp потому что это не шаблон!

Vector<double> Point::toVector()
{
    Vector<double> pointVector = Vector<double>(4);
    pointVector[0] = pX;
    pointVector[1] = pY;
    pointVector[2] = pZ;
    pointVector[3] = 1;

    return pointVector;
}

#endif
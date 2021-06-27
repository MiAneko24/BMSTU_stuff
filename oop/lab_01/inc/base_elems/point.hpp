#ifndef POINT_HPP
#define POINT_HPP
#include "vector.hpp"
#include <memory>
#define DIMENSION 3

class Point {
    public:
        Point() = default;
        Point(double x, double y, double z);
        Point(const Point &) = default;
        Point(const Vector<double> vector);
        Point &operator =(const Point&) = default;
        
        void transform(const Matrix<double> &transform_matrix);
        
        double getX() const;
        double getY() const;
        double getZ() const;
        Vector<double> toVector();
        void setFromVector(Vector<double> &vector);

    private:
        double pX;
        double pY;
        double pZ;
};


#endif
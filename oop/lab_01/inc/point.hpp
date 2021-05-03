#ifndef POINT_HPP
#define POINT_HPP

class Point {
    public:
        Point() = default;
        Point(double x, double y, double z): pX(x), pY(y), pZ(z) {};
        Point(const Point &) = default;
        Point &operator =(const Point&) = default;
        double getX() const {
            return pX;
        }
        double getY() const {
            return pY;
        }
        double getZ() const {
            return pZ;
        }
    private:
        double pX;
        double pY;
        double pZ;
};

#endif
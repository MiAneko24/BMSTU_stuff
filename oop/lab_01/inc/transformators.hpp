#ifndef TRANSFORMATORS_HPP
#define TRANSFORMATORS_HPP
#include "point.hpp"

class BaseTransformator {
    public:
        virtual Point transform(const Point &p) = 0;
};

class RotateTransformator : public BaseTransformator {
    public:
        RotateTransformator() = delete;
        RotateTransformator(double xAngle = 0, double yAngle = 0, double zAngle = 0) : rX(xAngle), rY(yAngle), rZ(zAngle) {};
        RotateTransformator(const RotateTransformator &) = delete;
        Point transform(const Point &p) override;
    private:
        double rX;
        double rY;
        double rZ;
};

class ScaleTransformator : public BaseTransformator {
    public:
        ScaleTransformator() = delete;
        ScaleTransformator(double xZoom = 0, double yZoom = 0, double zZoom = 0) : kX(xZoom), kY(yZoom), kZ(zZoom) {};
        ScaleTransformator(const ScaleTransformator &) = delete;
        Point transform(const Point &p) override;
    private:
        double kX;
        double kY;
        double kZ;
};

class MoveTransformator : public BaseTransformator {
    public:
        MoveTransformator() = delete;
        MoveTransformator(double xMove = 0, double yMove = 0, double zMove = 0) : dX(xMove), dY(yMove), dZ(zMove) {};
        MoveTransformator(const MoveTransformator &) = delete;
        Point transform(const Point &p) override;
    private:
        double dX;
        double dY;
        double dZ;
};

#endif
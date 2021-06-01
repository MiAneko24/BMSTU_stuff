#ifndef CAMERAPOSITION_H
#define CAMERAPOSITION_H

#include "../point.hpp"
#include "../vector.hpp"

class CameraPosition
{
    public:
        CameraPosition();
        const Point& getPosition() const;
        void setPosition(Point position);
        
        double getXAngle() const;
        void setXAngle(double x_angle);

        double getYAngle() const;
        void setYAngle(double y_angle);

        double getZAngle() const;
        void setZAngle(double z_angle);

        Point getProjection(Point& point);
        void transform(const Matrix<double> &transform_mat);
    
    private:
        Point position;
        Vector<double> angles = Vector<double>(3);
};

#endif
#ifndef CAMERAPOSITION_H
#define CAMERAPOSITION_H

#include "../base_elems/point.hpp"
#include "../base_elems/vector.hpp"

class CameraPosition
{
    public:
        CameraPosition();
        const Point& getPosition() const;
        void setPosition(Point position);
        
        double getXAngle() const;
        double getYAngle() const;
        double getZAngle() const;

        void setAngles(Vector<double> &new_angles);

        Point getProjection(Point& point);
        void transform(const Matrix<double> &transform_mat);

        ~CameraPosition() = default;
    
    private:
        Point position;
        Vector<double> angles = Vector<double>(3);
};

#endif
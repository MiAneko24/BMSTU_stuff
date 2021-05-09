#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "object.hpp"
#include "point.hpp"
class Camera : public Object
{
    public:
        Camera(std::string name);

        explicit Camera() = default;
        ~Camera() = default;

        bool isVisible() const final;

        const Point& getPosition() const;
        void setPosition(const Point &position);
        
        double getXAngle() const;
        double setXAngle(double x_angle);

        double getYAngle() const;
        double setYAngle(double y_angle);

        double getZAngle() const;
        double setZAngle(double z_angle);

        void transform(const std::shared_ptr<Matrix<double>> mat);

}

#endif
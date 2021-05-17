#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "object.hpp"
#include "point.hpp"
class Camera : public Object
{
    public:
        explicit Camera();

        bool isVisible() const final;

        const Point& getPosition() const;
        void setPosition(const Point &position);
        
        double getXAngle() const;
        void setXAngle(double x_angle);

        double getYAngle() const;
        void setYAngle(double y_angle);

        double getZAngle() const;
        void setZAngle(double z_angle);

        void transform(std::shared_ptr<Matrix<double>> mat) override;
    
        ~Camera() = default;
    private:
        Point position;
        Vector<double> angles = Vector<double>(3);
};

#endif
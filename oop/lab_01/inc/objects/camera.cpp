#include "camera.hpp"

Camera::Camera()
{
    this->position = Point(0, 0, 300);
}

bool Camera::isVisible() const
{
    return false;
}

const Point& Camera::getPosition() const
{
    return position;
}

double Camera::getXAngle() const
{
    return angles[0];
}

void Camera::setPosition(Point &position)
{
    this->position = position;
}

void Camera::setXAngle(double x_angle)
{
    angles[0] = x_angle;
}

double Camera::getYAngle() const
{
    return angles[1];
}

void Camera::setYAngle(double y_angle)
{
    angles[1] = y_angle;
}

double Camera::getZAngle() const
{
    return angles[2];
}

void Camera::setZAngle(double z_angle)
{
    angles[2] = z_angle;
}

void Camera::transform(const Matrix<double> &mat)
{
    position.transform(mat);
}

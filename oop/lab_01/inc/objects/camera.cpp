#include "camera.hpp"
#include "../draw/visitor.h"

Camera::Camera()
{
    this->position = std::shared_ptr<CameraPosition>(new CameraPosition());
}

bool Camera::isVisible() const
{
    return false;
}

std::shared_ptr<CameraPosition> Camera::getPosition()
{
    return position;
}

void Camera::transform(const Matrix<double> &mat)
{
    position->transform(mat);
}

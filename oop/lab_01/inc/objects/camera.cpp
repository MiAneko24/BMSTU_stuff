#include "camera.hpp"
#include "../draw/visitor.h"
#include "../draw/ObjectsVisitor.h"

Camera::Camera()
{
    this->position = std::shared_ptr<CameraPosition>(new CameraPosition());
    type = ObjectType::CAMERA;
}

Camera::Camera(std::shared_ptr<CameraPosition> pos) : position(pos) 
{
    type= ObjectType::CAMERA;
} 

ObjectType Camera::getType() const
{
    return type;
}

void Camera::transform(const Matrix<double> &mat)
{
    if (mat.getColumns() == mat.getRows())
        position->transform(mat);
    else
        position->setAngles(mat[0]);
}

void Camera::accept(Visitor &visitor)
{

}

Camera::~Camera()
{
    position.reset();
}


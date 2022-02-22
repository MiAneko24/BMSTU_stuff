#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "object.hpp"
#include "cameraPosition.h"

class ObjectsVisitor;

class Camera : public Object
{
    public:
        friend ObjectsVisitor;
        explicit Camera();
        Camera(std::shared_ptr<CameraPosition> pos);

        ObjectType getType() const override;

        void transform(const Matrix<double> &mat) override;
        void accept(Visitor &visitor) override;

        ~Camera();
    private:
        std::shared_ptr<CameraPosition> position;
};

#endif
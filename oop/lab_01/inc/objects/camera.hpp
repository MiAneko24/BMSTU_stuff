#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "object.hpp"
#include "cameraPosition.h"

class Camera : public Object
{
    public:
        explicit Camera();

        bool isVisible() const final override;

        void transform(const Matrix<double> &mat) override;
        void accept(Visitor &visitor) override;
        std::shared_ptr<CameraPosition> getPosition();

        ~Camera();
    private:
        std::shared_ptr<CameraPosition> position;
};

#endif
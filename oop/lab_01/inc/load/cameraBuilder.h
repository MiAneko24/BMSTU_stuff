#ifndef CAMERABUILDER_H
#define CAMERABUILDER_H
#include "baseBuilder.hpp"

class CameraBuilder : public BaseBuilder
{
    public:
        bool buildCamera(std::ifstream& file) override;
};

#endif
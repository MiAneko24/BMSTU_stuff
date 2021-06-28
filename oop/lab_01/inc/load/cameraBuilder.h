#ifndef CAMERABUILDER_H
#define CAMERABUILDER_H
#include "baseBuilder.hpp"
#include "../objects/cameraPosition.h"

class CameraBuilder : public BaseBuilder
{
    public:
        bool buildCamera(std::ifstream& file) override;
        bool buildModel(std::ifstream& file) override;
        ~CameraBuilder() = default;
        
    private:
        bool buildPosition(std::ifstream& file);
        bool buildAngles(std::ifstream &file);
        std::shared_ptr<CameraPosition> position;
};

#endif
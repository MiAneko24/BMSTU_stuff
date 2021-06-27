#ifndef CAMERABUILDER_H
#define CAMERABUILDER_H
#include "baseBuilder.hpp"

class CameraBuilder : public BaseBuilder
{
    public:
        bool buildCamera(std::ifstream& file) override;
        bool buildModel(std::ifstream& file) override;
        ~CameraBuilder() = default;
        
    private:
        bool buildPosition(std::ifstream& file);
        bool buildAngles(std::ifstream &file);
};

#endif
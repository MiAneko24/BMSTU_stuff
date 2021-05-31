#ifndef SCENEBUILDER_H
#define SCENEBUILDER_H
#include "cameraBuilder.h"
#include "modelBuilder.h"

class SceneBuilder : public BaseBuilder
{
    public: 
        bool buildModel(std::ifstream &file) override;
        bool buildCamera(std::ifstream &file) override;
    
    private:
        std::shared_ptr<CameraBuilder> cameraBuilder;
        std::shared_ptr<ModelBuilder> modelBuilder;
};

#endif
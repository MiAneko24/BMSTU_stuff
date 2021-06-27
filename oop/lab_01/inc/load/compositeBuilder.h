#ifndef COMPOSITEBUILDER_H
#define COMPOSITEBUILDER_H
#include "cameraBuilder.h"
#include "modelBuilder.h"

class CompositeBuilder : public BaseBuilder
{
    public: 
        bool buildModel(std::ifstream &file) override;
        bool buildCamera(std::ifstream &file) override;
        ~CompositeBuilder() = default;
    
    private:
        std::shared_ptr<CameraBuilder> cameraBuilder;
        std::shared_ptr<ModelBuilder> modelBuilder;
};

#endif
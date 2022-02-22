#ifndef COMPOSITEBUILDER_H
#define COMPOSITEBUILDER_H
#include "cameraBuilder.h"
#include "modelBuilder.h"

class CompositeBuilder : public BaseBuilder
{
    public: 
        CompositeBuilder();
        bool isBuilt() override;
        bool buildModel() override;
        bool buildCamera() override;
        bool buildPoints(Vector<Point> &point) override;
        bool buildAngles(Vector<double> &angles) override;
        bool buildConnections(Vector<Connection> &connection) override; 
        bool buildPosition(Point &point) override;
        ~CompositeBuilder() = default;
    
    private:
        bool built;
        std::shared_ptr<CameraBuilder> cameraBuilder;
        std::shared_ptr<ModelBuilder> modelBuilder;
};

#endif
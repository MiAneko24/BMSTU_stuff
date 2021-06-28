#ifndef MODELBUILDER_H
#define MODELBUILDER_H
#include "baseBuilder.hpp"
#include "../base_elems/point.hpp"
#include "../base_elems/connection.hpp"
#include "../base_elems/vector.hpp"
#include "../objects/frameModel.h"

class ModelBuilder : public BaseBuilder
{
    public:
        bool buildModel() override;
        bool buildPoints(Vector<Point> &points) override;
        bool buildConnections(Vector<Connection> &connections) override;
        ~ModelBuilder() = default;
        
    private:
        std::shared_ptr<FrameModel> frame;
};

#endif
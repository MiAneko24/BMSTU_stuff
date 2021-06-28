#include "compositeBuilder.h"
#include "../objects/scene.hpp"

CompositeBuilder::CompositeBuilder()
{
    built = false;
    modelBuilder.reset(new ModelBuilder());
    cameraBuilder.reset(new CameraBuilder());
}

bool CompositeBuilder::buildModel()
{
    if (!object)
        object.reset(new CompositeObject());
    object->add(modelBuilder->getObject());
    built = true;
    return true;
}

bool CompositeBuilder::buildCamera()
{
    if (!object)
        object.reset(new CompositeObject());
    if (!cameraBuilder)
        cameraBuilder.reset(new CameraBuilder());
    
    object->add(cameraBuilder->getObject());
    built = true;
    return true;
}

bool CompositeBuilder::buildPoints(Vector<Point> &point)
{
    built = false;
    return modelBuilder->buildPoints(point);
}

bool CompositeBuilder::buildAngles(Vector<double> &angles)
{
    built = false;
    return cameraBuilder->buildAngles(angles);
}

bool CompositeBuilder::buildConnections(Vector<Connection> &connection)
{
    built = false;
    return modelBuilder->buildConnections(connection);
}

bool CompositeBuilder::buildPosition(Point &position)
{
    built = false;
    return cameraBuilder->buildPosition(position);
}

bool CompositeBuilder::isBuilt()
{
    return built;
}
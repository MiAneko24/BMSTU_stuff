#include "compositeBuilder.h"
#include "../objects/scene.hpp"

CompositeBuilder::CompositeBuilder()
{
    modelBuilder.reset(new ModelBuilder());
    cameraBuilder.reset(new CameraBuilder());
}

bool CompositeBuilder::buildModel()
{
    if (!object)
        object.reset(new CompositeObject());
    object->add(modelBuilder->getObject());
    return true;
}

bool CompositeBuilder::buildCamera()
{
    if (!object)
        object.reset(new CompositeObject());
    if (!cameraBuilder)
        cameraBuilder.reset(new CameraBuilder());
    
    object->add(cameraBuilder->getObject());
    return true;
}

bool CompositeBuilder::buildPoints(Vector<Point> &point)
{
    bool flag = true;
    flag = modelBuilder->buildPoints(point);
    return flag;
}

bool CompositeBuilder::buildAngles(Vector<double> &angles)
{
    return cameraBuilder->buildAngles(angles);
}

bool CompositeBuilder::buildConnections(Vector<Connection> &connection)
{
    return modelBuilder->buildConnections(connection);
}

bool CompositeBuilder::buildPosition(Point &position)
{
    bool flag = cameraBuilder->buildPosition(position);
    return flag;
}
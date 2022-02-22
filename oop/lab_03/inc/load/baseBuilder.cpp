#include "baseBuilder.hpp"

BaseBuilder::~BaseBuilder() = default;

bool BaseBuilder::buildAngles(Vector<double> &angles)
{
    return true;
}

bool BaseBuilder::buildConnections(Vector<Connection> &connection)
{
    return true;
}

bool BaseBuilder::buildPoints(Vector<Point> &points)
{
    return true;
}

bool BaseBuilder::buildPosition(Point &point)
{
    return true;
}

bool BaseBuilder::buildModel()
{
    return true;
}

bool BaseBuilder::buildCamera()
{
    return true;
}

std::shared_ptr<Object> BaseBuilder::getObject()
{
    return object;
}


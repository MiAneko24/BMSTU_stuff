#include "cameraBuilder.h"
#include "../objects/camera.hpp"
#include "../objects/cameraPosition.h"
#include "../base_elems/point.hpp"
#include "../base_elems/exceptions.hpp"

CameraBuilder::CameraBuilder()
{
    position.reset(new CameraPosition());
    builtParts = 0;
}

bool CameraBuilder::buildCamera()
{
    object.reset(new Camera(position));
    return true;
}

bool CameraBuilder::isBuilt()
{
    if (builtParts == 2)
        return true;
    return false;
}

bool CameraBuilder::buildAngles(Vector<double> &angles)
{
    builtParts++;
    position->setAngles(angles);
    return true;
}

bool CameraBuilder::buildPosition(Point &point)
{
    builtParts++;
    position->setPosition(point);
    return true;
}
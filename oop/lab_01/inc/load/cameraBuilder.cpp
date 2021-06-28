#include "cameraBuilder.h"
#include "../objects/camera.hpp"
#include "../objects/cameraPosition.h"
#include "../base_elems/point.hpp"
#include "../base_elems/exceptions.hpp"

bool CameraBuilder::buildCamera()
{
    position.reset(new CameraPosition());
    object.reset(new Camera(position));
    return true;
}


bool CameraBuilder::buildAngles(Vector<double> &angles)
{
    position->setAngles(angles);
    return true;
}

bool CameraBuilder::buildPosition(Point &point)
{
    position->setPosition(point);
    return true;
}
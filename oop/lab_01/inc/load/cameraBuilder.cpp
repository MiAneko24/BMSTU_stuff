#include "cameraBuilder.h"
#include "../point.hpp"
#include "../objects/camera.hpp"
#include "../objects/cameraPosition.h"
#include "../exceptions.hpp"

bool CameraBuilder::buildCamera(std::ifstream& file)
{
    object.reset(new Camera());
    return buildPosition(file) && buildAngles(file);
}

bool CameraBuilder::buildPosition(std::ifstream& file)
{
    bool state = true;
    double x, y, z;
    if (file >> x >> y >> z)
    {
        std::shared_ptr<Camera> camera = std::dynamic_pointer_cast<Camera>(object);
        camera->getPosition()->setPosition(Point(x, y, z));
    }
    else
    {
        time_t t_time = time(NULL);
        throw FileDataError(ctime(&t_time), __FILE__, typeid(*this).name(), __LINE__);
    }
    return state;
}

bool CameraBuilder::buildAngles(std::ifstream& file)
{
    bool state = true;
    double x, y, z;
    if (file >> x >> y >> z)
    {
        std::shared_ptr<Camera> camera = std::dynamic_pointer_cast<Camera>(object);
        camera->getPosition()->setXAngle(x);
        camera->getPosition()->setYAngle(y);
        camera->getPosition()->setZAngle(z);
    }
    else 
    {
        time_t t_time = time(NULL);
        throw FileDataError(ctime(&t_time), __FILE__, typeid(*this).name(), __LINE__);
    }
    return state;
}

bool CameraBuilder::buildModel(std::ifstream& file)
{
    return BaseBuilder::buildModel(file);
}
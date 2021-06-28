#include "cameraBuilder.h"
#include "../objects/camera.hpp"
#include "../objects/cameraPosition.h"
#include "../base_elems/point.hpp"
#include "../base_elems/exceptions.hpp"

bool CameraBuilder::buildCamera(std::ifstream& file)
{
    position.reset(new CameraPosition());
    bool flag = buildPosition(file) && buildAngles(file);
    if (flag)
        object.reset(new Camera(position));
    return flag;
}

bool CameraBuilder::buildPosition(std::ifstream& file)
{
    bool state = true;
    double x, y, z;
    if (file >> x >> y >> z)
    {
        std::shared_ptr<Camera> camera = std::dynamic_pointer_cast<Camera>(object);
        position->setPosition(Point(x, y, z));
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
        Vector<double> vect = Vector<double>({x, y, z}, 3);
        position->setAngles(vect);
    }
    else 
    {
        time_t t_time = time(NULL);
        throw FileDataError(ctime(&t_time), __FILE__, typeid(*this).name(), __LINE__);
    }
    return state;
}

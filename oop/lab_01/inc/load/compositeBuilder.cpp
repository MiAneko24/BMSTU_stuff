#include "compositeBuilder.h"
#include "../objects/scene.hpp"

bool CompositeBuilder::buildModel(std::ifstream& file)
{
    if (!object)
        object.reset(new CompositeObject());
    if (!modelBuilder)
        modelBuilder.reset(new ModelBuilder());
    int amount = 0;
    if (!(file >> amount && amount > 0))
    {
        time_t t_time = time(NULL);
        throw FileDataError(ctime(&t_time), __FILE__, typeid(*this).name(), __LINE__);
    }
    for (int i = 0; i < amount; i++)
    {
        if (modelBuilder->buildModel(file))
        {

            object->add(modelBuilder->getObject());
        }
        else
        {        
            time_t t_time = time(NULL);
            throw FileDataError(ctime(&t_time), __FILE__, typeid(*this).name(), __LINE__);
        }
    }
    return true;
}

bool CompositeBuilder::buildCamera(std::ifstream& file)
{
    if (!object)
        object.reset(new CompositeObject());
    if (!cameraBuilder)
        cameraBuilder.reset(new CameraBuilder());
    bool state = true;
    int amount = 0;
    if (!(file >> amount && amount > 0))
    {
        time_t t_time = time(NULL);
        throw FileDataError(ctime(&t_time), __FILE__, typeid(*this).name(), __LINE__);
    }
    for (int i = 0; i < amount && state; i++)
    {
        if (cameraBuilder->buildCamera(file))
        {   
            object->add(cameraBuilder->getObject());
        }
        else
        {
            time_t t_time = time(NULL);
            throw FileDataError(ctime(&t_time), __FILE__, typeid(*this).name(), __LINE__);
    
        }
    }
    return state;
}
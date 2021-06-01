#include "sceneBuilder.h"
#include "../objects/scene.hpp"

bool SceneBuilder::buildModel(std::ifstream& file)
{
    if (!object)
        object.reset(new Scene());
    if (!modelBuilder)
        modelBuilder.reset(new ModelBuilder());
    bool state = true;
    int amount = 0;
    if (!(file >> amount && amount > 0))
    {
        time_t t_time = time(NULL);
        throw FileDataError(ctime(&t_time), __FILE__, typeid(*this).name(), __LINE__);
    }
    std::shared_ptr<Scene> scene = std::dynamic_pointer_cast<Scene>(object);
    for (int i = 0; i < amount && state; i++)
    {
        if (modelBuilder->buildModel(file))
        {
            scene->add(modelBuilder->getObject());
        }
        else
        {        
            time_t t_time = time(NULL);
            throw FileDataError(ctime(&t_time), __FILE__, typeid(*this).name(), __LINE__);
        }
    }
    
    return state;
}

bool SceneBuilder::buildCamera(std::ifstream& file)
{
    if (!object)
        object.reset(new Scene());
    if (!cameraBuilder)
        cameraBuilder.reset(new CameraBuilder());
    bool state = true;
    int amount = 0;
    if (!(file >> amount && amount > 0))
    {
        time_t t_time = time(NULL);
        throw FileDataError(ctime(&t_time), __FILE__, typeid(*this).name(), __LINE__);
    }
    std::shared_ptr<Scene> scene = std::dynamic_pointer_cast<Scene>(object);
    for (int i = 0; i < amount && state; i++)
    {
        if (cameraBuilder->buildCamera(file))
        {
            scene->add(cameraBuilder->getObject());
        }
        else
        {
            time_t t_time = time(NULL);
            throw FileDataError(ctime(&t_time), __FILE__, typeid(*this).name(), __LINE__);
    
        }
    }
    return state;
}
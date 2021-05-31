#include "sceneManagerCreator.h"
#include "../sceneManager.hpp"

std::shared_ptr<SceneManager> SceneManagerCreator::createManager()
{
    return std::shared_ptr<SceneManager>(new SceneManager());
}


std::shared_ptr<SceneManager> SceneManagerCreator::getManager()
{
    if (!manager) 
    {
        manager = createManager();
    }
    return manager;
}

#include "sceneManagerCreator.h"
#include "../sceneManager.hpp"

void SceneManagerCreator::createManager()
{
    static std::shared_ptr<SceneManager> mng(new SceneManager());
    manager = mng;
}


std::shared_ptr<SceneManager> SceneManagerCreator::getManager()
{
    if (!manager) 
    {
        createManager();
    }
    return manager;
}

#include "drawManagerCreator.h"
#include "../drawManager.hpp"

std::shared_ptr<DrawManager> DrawManagerCreator::createManager()
{
    return std::shared_ptr<DrawManager>(new DrawManager(SceneManagerCreator().getManager()));
}

std::shared_ptr<DrawManager> DrawManagerCreator::getManager()
{
    if (!manager) 
    {
        manager = createManager();
    }
    return manager;
}

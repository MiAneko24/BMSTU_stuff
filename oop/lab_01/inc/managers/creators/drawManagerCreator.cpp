#include "drawManagerCreator.h"
#include "../drawManager.hpp"


void DrawManagerCreator::createManager()
{
    static std::shared_ptr<DrawManager> mng(new DrawManager(SceneManagerCreator().getManager()));
    manager = mng;
}

std::shared_ptr<DrawManager> DrawManagerCreator::getManager()
{
    if (!manager) 
    {
        createManager();
    }
    return manager;
}

#include "loadManagerCreator.h"
#include "../loadManager.hpp"

void LoadManagerCreator::createManager()
{
    static std::shared_ptr<LoadManager> mng(new LoadManager(SceneManagerCreator().getManager()));
    manager = mng;
}

std::shared_ptr<LoadManager> LoadManagerCreator::getManager()
{
    if (!manager) 
    {
        createManager();
    }
    return manager;
}

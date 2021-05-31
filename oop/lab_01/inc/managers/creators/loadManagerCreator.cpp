#include "loadManagerCreator.h"
#include "../loadManager.hpp"

std::shared_ptr<LoadManager> LoadManagerCreator::createManager()
{
    return std::shared_ptr<LoadManager>(new LoadManager(SceneManagerCreator().getManager()));
}

std::shared_ptr<LoadManager> LoadManagerCreator::getManager()
{
    if (!manager) 
    {
        manager = createManager();
    }
    return manager;
}

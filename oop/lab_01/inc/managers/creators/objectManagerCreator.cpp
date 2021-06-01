#include "objectManagerCreator.h"
#include "../objectManager.hpp"

std::shared_ptr<ObjectManager> ObjectManagerCreator::createManager()
{
    return std::shared_ptr<ObjectManager>(new ObjectManager(SceneManagerCreator().getManager()));
}

std::shared_ptr<ObjectManager> ObjectManagerCreator::getManager()
{
    if (!manager) 
    {
        manager = createManager();
    }
    return manager;
}

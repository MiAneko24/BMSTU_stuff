#include "objectManagerCreator.h"
#include "../objectManager.hpp"

ObjectManagerCreator::ObjectManagerCreator(std::shared_ptr<SceneManagerCreator> creator)
{
    sceneManagerCreator = creator;
}

std::shared_ptr<ObjectManager> ObjectManagerCreator::createManager()
{
    return std::shared_ptr<ObjectManager>(new ObjectManager(sceneManagerCreator->getManager()));
}

std::shared_ptr<ObjectManager> ObjectManagerCreator::getManager()
{
    if (!manager) 
    {
        manager = createManager();
    }
    return manager;
}

#include "objectManagerCreator.h"
#include "../objectManager.hpp"

void ObjectManagerCreator::createManager()
{
    static std::shared_ptr<ObjectManager> mng(new ObjectManager(SceneManagerCreator().getManager()));
    manager = mng;
}

std::shared_ptr<ObjectManager> ObjectManagerCreator::getManager()
{
    if (!manager) 
    {
        createManager();
    }
    return manager;
}

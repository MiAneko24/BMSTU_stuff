#include "transformManagerCreator.h"
#include "../transformManager.h"


std::shared_ptr<TransformManager> TransformManagerCreator::createManager()
{
    return std::shared_ptr<TransformManager>(new TransformManager(SceneManagerCreator().getManager()));
}


std::shared_ptr<TransformManager> TransformManagerCreator::getManager()
{
    if (!manager) 
    {
        manager = createManager();
    }
    return manager;
}

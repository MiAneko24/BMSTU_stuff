#include "transformManagerCreator.h"
#include "../transformManager.h"

void TransformManagerCreator::createManager()
{
    static std::shared_ptr<TransformManager> mng(new TransformManager(SceneManagerCreator().getManager()));
    manager = mng;
}


std::shared_ptr<TransformManager> TransformManagerCreator::getManager()
{
    if (!manager) 
    {
        createManager();
    }
    return manager;
}

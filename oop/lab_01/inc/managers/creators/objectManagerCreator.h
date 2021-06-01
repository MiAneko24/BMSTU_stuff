#ifndef OBJECTMANAGERCREATOR_H
#define OBJECTMANAGERCREATOR_H
#include "sceneManagerCreator.h"
#include <memory>
#include "../objectManager.hpp"

class ObjectManagerCreator
{
    public:
        std::shared_ptr<ObjectManager> getManager();

    private:
        std::shared_ptr<SceneManagerCreator> sceneManagerCreator;
        std::shared_ptr<ObjectManager> manager;
        std::shared_ptr<ObjectManager> createManager();
};

#endif
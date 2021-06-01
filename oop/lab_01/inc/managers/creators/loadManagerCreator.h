#ifndef LOADMANAGERCREATOR_H
#define LOADMANAGERCREATOR_H
#include "sceneManagerCreator.h"
#include <memory>
#include "../loadManager.hpp"

class LoadManagerCreator
{
    public:
        std::shared_ptr<LoadManager> getManager();

    private:
        std::shared_ptr<LoadManager> manager;
        std::shared_ptr<LoadManager> createManager();
};

#endif
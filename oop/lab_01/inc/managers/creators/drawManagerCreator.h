#ifndef DRAWMANAGERCREATOR_H
#define DRAWMANAGERCREATOR_H
#include "sceneManagerCreator.h"
#include <memory>
#include "../drawManager.hpp"

class DrawManagerCreator
{
    public:
        std::shared_ptr<DrawManager> getManager();

    private:
        std::shared_ptr<DrawManager> manager;
        std::shared_ptr<DrawManager> createManager();
};

#endif
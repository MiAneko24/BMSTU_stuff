#ifndef DRAWMANAGERCREATOR_H
#define DRAWMANAGERCREATOR_H
#include "sceneManagerCreator.h"

class DrawManagerCreator
{
    public:
        std::shared_ptr<DrawManager> getManager();

    private:
        std::shared_ptr<DrawManager> manager;
        std::shared_ptr<DrawManager> createManager();
};

#endif
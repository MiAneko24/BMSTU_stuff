#ifndef TRANSFORMMANAGERCREATOR_H
#define TRANSFORMMANAGERCREATOR_H
#include "sceneManagerCreator.h"

class TransformManagerCreator
{
    public:
        std::shared_ptr<TransformManager> getManager();
    private:
        std::shared_ptr<TransformManager> manager;
        std::shared_ptr<TransformManager> createManager();
    
};

#endif
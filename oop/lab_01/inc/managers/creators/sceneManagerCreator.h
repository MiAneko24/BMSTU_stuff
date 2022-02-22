#ifndef SCENEMANAGERCREATOR_H
#define SCENEMANAGERCREATOR_H
#include <memory>
#include "../sceneManager.hpp"

class SceneManagerCreator
{
    public:
        std::shared_ptr<SceneManager> getManager();

    private:
        std::shared_ptr<SceneManager> manager;
        void createManager();
    
};


#endif
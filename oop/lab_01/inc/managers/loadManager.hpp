#ifndef LOADMANAGER_HPP
#define LOADMANAGER_HPP

#include "baseManager.hpp"
#include <iostream>
#include "sceneManager.hpp"
#include "../load/baseLoader.hpp"

class LoadManager : public BaseManager
{
    public:
        LoadManager(std::shared_ptr<SceneManager> manager);
        void loadObject(ObjectType type_obj, std::string filename);
        ~LoadManager();
    
    private:
        std::shared_ptr<SceneManager> sceneManager;
        std::shared_ptr<BaseLoader> loader;
};

#endif
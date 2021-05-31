#include "loadManager.hpp"

LoadManager::LoadManager(std::shared_ptr<SceneManager> manager)
{
    sceneManager = manager;
}

void LoadManager::loadObject(ObjectType type_obj, std::string filename)
{
    if (!loader)
        loader.reset(new BaseLoader());
    std::shared_ptr<Object> obj = loader->loadModel(type_obj, filename);
    sceneManager->getScene()->add(obj);
}
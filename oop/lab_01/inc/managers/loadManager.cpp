#include "loadManager.hpp"

LoadManager::LoadManager(std::shared_ptr<SceneManager> manager)
{
    sceneManager = manager;
}

void LoadManager::loadObject(ObjectType type_obj, std::string filename)
{
    if (!loader) {
        loader = std::shared_ptr<BaseLoader>(new BaseLoader());
    }
    int amount = sceneManager->getObjectsAmount(type_obj);
    std::shared_ptr<Object> obj = loader->loadObject(type_obj, filename);
    int curScene = sceneManager->getCurrentObjectPos(ObjectType::COMPOSITE);
    sceneManager->getScene()->add(type_obj, obj, curScene);
    if (type_obj == ObjectType::COMPOSITE)
        sceneManager->setCurrentObjectPos(type_obj, amount);
}

LoadManager::~LoadManager()
{
    sceneManager.reset();
    loader.reset();
}
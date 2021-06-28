#include "loadManager.hpp"
#include "../load/compositeBuilder.h"

LoadManager::LoadManager(std::shared_ptr<SceneManager> manager)
{
    sceneManager = manager;
}

void LoadManager::loadObject(ObjectType type_obj, std::string filename)
{
    if (!loader) 
    {
        loader = std::shared_ptr<BaseLoader>(new BaseLoader());
    }
    if (!director)
    {
        director = std::shared_ptr<Director>(new Director());
        director->setLoader(loader);
    }

    std::shared_ptr<BaseBuilder> builder;
    switch (type_obj)
    {
        case ObjectType::MODEL:
            builder.reset(new ModelBuilder());
            break;
        case ObjectType::COMPOSITE:
            builder.reset(new CompositeBuilder());
        
        default:
            break;
    }
    int amount = sceneManager->getObjectsAmount(type_obj);
    std::shared_ptr<Object> obj = director->create(type_obj, builder, filename);
    int curScene = sceneManager->getCurrentObjectPos(ObjectType::COMPOSITE);
    sceneManager->getScene()->add(type_obj, obj, curScene);
    if (type_obj == ObjectType::COMPOSITE)
        sceneManager->setCurrentObjectPos(type_obj, amount);
}

LoadManager::~LoadManager()
{
    sceneManager.reset();
    loader.reset();
    director.reset();
}
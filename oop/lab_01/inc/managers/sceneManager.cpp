#include "sceneManager.hpp"

SceneManager::SceneManager()
{
    scene = std::shared_ptr<Scene>(new Scene());
    curCamera = 0;
    curModel = 0;
    curScene = 0;
}

void SceneManager::addScene(std::shared_ptr<Object> new_scene)
{
    scene->add(ObjectType::COMPOSITE, new_scene, curScene);
}

std::shared_ptr<Scene> SceneManager::getScene()
{
    return scene;
}

void SceneManager::setCurrentObjectPos(ObjectType type_obj, int pos)
{
    if (type_obj == ObjectType::CAMERA)
        curCamera = pos;
    else if (type_obj == ObjectType::MODEL)
        curModel = pos;
    else if (type_obj == ObjectType::COMPOSITE)
        curScene = pos;
}

int SceneManager::getCurrentObjectPos(ObjectType type_obj)
{
    int pos = -1;
    if (type_obj == ObjectType::CAMERA)
        pos = curCamera;
    else if (type_obj == ObjectType::MODEL)
        pos = curModel;
    else if (type_obj == ObjectType::COMPOSITE)
        pos = curScene;
    return pos;
}

int SceneManager::getObjectsAmount(ObjectType type_obj)
{
    return scene->getObjectsAmount(type_obj, curScene);
}

SceneManager::~SceneManager()
{
    scene.reset();
}
#include "sceneManager.hpp"

void SceneManager::setScene(std::shared_ptr<Scene> new_scene)
{
    scene = new_scene;
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
}

int SceneManager::getCurrentObjectPos(ObjectType type_obj)
{
    int pos = -1;
    if (type_obj == ObjectType::CAMERA)
        pos = curCamera;
    else if (type_obj == ObjectType::MODEL)
        pos = curModel;
    return pos;
}
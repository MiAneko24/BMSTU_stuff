#include "sceneManager.hpp"

SceneManager::SceneManager()
{
    scene = Scene();
    curCamera = 0;
    curModel = 0;
}

std::shared_ptr<Object> SceneManager::getObject(ObjectType type_obj)
{
    //check?
    return (type_obj == ObjectType::MODEL) ? scene.getObject(type_obj, curModel) : scene.getObject(type_obj, curCamera);
}

void SceneManager::addObject(std::shared_ptr<Object> obj)
{
    scene.add(obj);
}

void SceneManager::removeObject(ObjectType type_obj)
{
    int index = (type_obj == ObjectType::MODEL) ? curModel : curCamera;
    VectorIterator<std::shared_ptr<Object>> it = scene.getIterator(type_obj, index);
    scene.remove(it);
}

void SceneManager::changeObject(ObjectType type_obj, int diff)
{
    if (type_obj == ObjectType::CAMERA)
        curCamera += diff;
    else if (type_obj == ObjectType::MODEL)
        curModel += diff;
    else
    {
        //throw error
    }
}
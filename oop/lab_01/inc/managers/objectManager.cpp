#include "objectManager.hpp"
#include "../base_elems/matrix.hpp"
#include "../objects/camera.hpp"

ObjectManager::ObjectManager(std::shared_ptr<SceneManager> manager)
{
    sceneManager = manager;
}

void ObjectManager::removeObject(ObjectType type_obj)
{
    std::shared_ptr<Scene> scene = sceneManager->getScene();
    int pos = sceneManager->getCurrentObjectPos(type_obj);
    if (pos == sceneManager->getObjectsAmount(type_obj) - 1 && pos != 0)
        sceneManager->setCurrentObjectPos(type_obj, pos - 1);
    int curScene = sceneManager->getCurrentObjectPos(ObjectType::COMPOSITE);
    VectorIterator<std::shared_ptr<Object>> iter = scene->getIterator(type_obj, pos, curScene);
    scene->remove(type_obj, iter, curScene);
}

void ObjectManager::changeCurrentObject(ObjectType type_obj, int new_pos)
{
    sceneManager->setCurrentObjectPos(type_obj, new_pos);
}

void ObjectManager::addObject(ObjectType type_obj)
{
    if (type_obj == ObjectType::CAMERA)
    {
        int curScene = sceneManager->getCurrentObjectPos(ObjectType::COMPOSITE);
        sceneManager->getScene()->add(type_obj, std::shared_ptr<Object>(new Camera()), curScene);
    }
}

void ObjectManager::getObjectsAmount(ObjectType type_obj, int& amount) 
{
    amount = sceneManager->getObjectsAmount(type_obj);
}

ObjectManager::~ObjectManager()
{
    sceneManager.reset();
}
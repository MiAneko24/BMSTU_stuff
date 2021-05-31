#include "objectManager.hpp"
#include "../matrix.hpp"
#include "../objects/camera.hpp"

ObjectManager::ObjectManager(std::shared_ptr<SceneManager> manager)
{
    sceneManager = manager;
}

void ObjectManager::removeObject(ObjectType type_obj)
{
    std::shared_ptr<Scene> scene = sceneManager->getScene();
    int pos = sceneManager->getCurrentObjectPos(type_obj);
    VectorIterator<std::shared_ptr<Object>> iter = scene->getIterator(type_obj, pos);
    scene->remove(iter);
}

void ObjectManager::changeCurrentObject(ObjectType type_obj, int diff)
{
    int cur_pos = sceneManager->getCurrentObjectPos(type_obj);
    sceneManager->setCurrentObjectPos(type_obj, cur_pos + diff);
    //всякие исключения продумать надо
}

void ObjectManager::addObject(ObjectType type_obj)
{
    if (type_obj == ObjectType::CAMERA)
        sceneManager->getScene()->add(std::shared_ptr<Object>(new Camera()));
}


// std::shared_ptr<Object> ObjectManager::getObject(ObjectType type_obj)
// {
//     //check?
//     return (type_obj == ObjectType::MODEL) ? scene.getObject(type_obj, curModel) : scene.getObject(type_obj, curCamera);
// }

// void ObjectManager::addObject(std::shared_ptr<Object> obj)
// {
//     scene.add(obj);
// }

// void ObjectManager::removeObject(ObjectType type_obj)
// {
//     int index = (type_obj == ObjectType::MODEL) ? curModel : curCamera;
//     VectorIterator<std::shared_ptr<Object>> it = scene.getIterator(type_obj, index);
//     scene.remove(it);
// }

// void ObjectManager::changeObject(ObjectType type_obj, int diff)
// {
//     if (type_obj == ObjectType::CAMERA)
//         curCamera += diff;
//     else if (type_obj == ObjectType::MODEL)
//         curModel += diff;
//     else
//     {
//         //throw error
//     }
// }
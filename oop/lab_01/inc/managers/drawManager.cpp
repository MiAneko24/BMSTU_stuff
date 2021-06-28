#include "drawManager.hpp"
#include "../draw/QtDrawerFactory.h"
#include "../draw/QTDrawer.h"
#include "../draw/ObjectsVisitor.h"

DrawManager::DrawManager(std::shared_ptr<SceneManager> manager)
{
    sceneManager = std::shared_ptr<SceneManager>(manager);
    drawer = std::shared_ptr<Drawer>();
}

void DrawManager::setDrawer(std::shared_ptr<Drawer> new_drawer)
{
    drawer = std::shared_ptr<Drawer>(new_drawer);
}

void DrawManager::drawModel()
{
    drawer->clear();
    if (sceneManager->getObjectsAmount(ObjectType::CAMERA) > 0 && sceneManager->getObjectsAmount(ObjectType::MODEL) > 0)
    {
        int pos = sceneManager->getCurrentObjectPos(ObjectType::CAMERA);
        int curScene = sceneManager->getCurrentObjectPos(ObjectType::COMPOSITE);
        auto it_cam = sceneManager->getScene()->getIterator(ObjectType::CAMERA, pos, curScene);
        auto it = sceneManager->getScene()->getIterator(ObjectType::COMPOSITE, curScene, curScene);
        ObjectsVisitor visitor(drawer, *it_cam);
        (*it)->accept(visitor);
    }
}


DrawManager::~DrawManager() {
    drawer.reset();
    sceneManager.reset();
}
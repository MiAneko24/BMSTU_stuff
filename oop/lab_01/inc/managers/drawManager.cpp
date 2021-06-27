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
    int pos = sceneManager->getCurrentObjectPos(ObjectType::CAMERA);
    int curScene = sceneManager->getCurrentObjectPos(ObjectType::COMPOSITE);
    std::shared_ptr<Camera> cam = std::dynamic_pointer_cast<Camera>(sceneManager->getScene()->getObject(ObjectType::CAMERA, pos, curScene));
    std::shared_ptr<Object> object = sceneManager->getScene()->getObject(ObjectType::COMPOSITE, curScene, curScene);
    ObjectsVisitor visitor(drawer, cam);
    object->accept(visitor);
}


DrawManager::~DrawManager() {
    drawer.reset();
    sceneManager.reset();
}
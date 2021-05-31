#include "drawManager.hpp"

DrawManager::DrawManager(std::shared_ptr<SceneManager> manager)
{
    sceneManager = manager;
}

void DrawManager::setDrawer(std::shared_ptr<Drawer> new_drawer)
{
    drawer = new_drawer;
}

void DrawManager::drawModel()
{
    int pos = sceneManager->getCurrentObjectPos(ObjectType::CAMERA);
    cam = std::dynamic_pointer_cast<Camera>(sceneManager->getScene()->getObject(ObjectType::CAMERA, pos));
    
    pos = sceneManager->getCurrentObjectPos(ObjectType::MODEL);
    std::shared_ptr<Object> model = sceneManager->getScene()->getObject(ObjectType::MODEL, pos);
    model->accept(std::shared_ptr<Visitor>(this));
}

void DrawManager::visit(Model &model)
{
    Vector<Point> project_points =  model.getFrame()->getPoints();
    for (auto point : project_points)
    {
        point = cam->getPosition()->getProjection(point);
    }
    for (auto connection : model.getFrame()->getConnections())
    {
        drawer->drawLine(
            project_points[connection.getFirst()], project_points[connection.getSecond()]
        );
    }
}
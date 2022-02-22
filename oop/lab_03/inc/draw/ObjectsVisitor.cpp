#include "ObjectsVisitor.h"

ObjectsVisitor::ObjectsVisitor(std::shared_ptr<Drawer> draw, std::shared_ptr<Object> cam) : drawer(draw), camera(cam) {};

void ObjectsVisitor::visit(Model &model)
{
    std::shared_ptr<Camera> cam = std::dynamic_pointer_cast<Camera>(camera);
    std::shared_ptr<CameraPosition> pos = (*cam).position;
    Vector<Point> project_points =  model.frame->getPoints();
    Vector<Point> projected = Vector<Point>(0);
    for (auto point : project_points)
    {
        point = pos->getProjection(point);
        projected.add(point);
    }
    
    for (auto connection : model.frame->getConnections())
    {
        drawer->drawLine(
            projected[connection.getFirst()], projected[connection.getSecond()]
        );
    }
}

void ObjectsVisitor::visit(Camera& camera)
{

}

void ObjectsVisitor::visit(CompositeObject& composite)
{

}
#include "ObjectsVisitor.h"

ObjectsVisitor::ObjectsVisitor(std::shared_ptr<Drawer> draw, std::shared_ptr<Camera> cam) : drawer(draw), camera(cam) {};

void ObjectsVisitor::visit(Model &model)
{
    Vector<Point> project_points =  model.getFrame()->getPoints();
    Vector<Point> projected = Vector<Point>(0);
    for (auto point : project_points)
    {
        point = camera->getPosition()->getProjection(point);
        projected.add(point);
    }
    
    for (auto connection : model.getFrame()->getConnections())
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
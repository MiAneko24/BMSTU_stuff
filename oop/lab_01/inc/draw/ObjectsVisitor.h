#ifndef OBJECTSVISITOR_H
#define OBJECTSVISITOR_H
#include "visitor.h"
#include "../objects/camera.hpp"
#include "drawer.h"

class ObjectsVisitor : public Visitor
{
    public:
        ObjectsVisitor(std::shared_ptr<Drawer> draw, std::shared_ptr<Camera> cam);
        void visit(Model &model) override;
        void visit(Camera &camera) override;
        void visit(CompositeObject &composite) override;
        ~ObjectsVisitor() = default;
    
    protected:
        std::shared_ptr<Drawer> drawer;
        std::shared_ptr<Camera> camera;
};

#endif
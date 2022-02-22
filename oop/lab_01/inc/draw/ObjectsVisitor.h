#ifndef OBJECTSVISITOR_H
#define OBJECTSVISITOR_H
#include "drawer.h"
#include "visitor.h"

class ObjectsVisitor : public Visitor
{
    public:
        ObjectsVisitor(std::shared_ptr<Drawer> draw, std::shared_ptr<Object> cam);
        void visit(Model &model) override;
        void visit(Camera &camera) override;
        void visit(CompositeObject &composite) override;
        ~ObjectsVisitor() = default;
    
    protected:
        std::shared_ptr<Drawer> drawer;
        std::shared_ptr<Object> camera;
};

#endif
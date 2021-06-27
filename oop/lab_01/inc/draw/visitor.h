#ifndef VISITOR_H
#define VISITOR_H
#include "../objects/camera.hpp"
#include "../objects/model.hpp"
#include "../objects/compositeObject.hpp"

class Visitor
{
    public:
        virtual void visit(Model &) = 0;
        virtual void visit(Camera &) = 0;
        virtual void visit(CompositeObject &) = 0; 
        virtual ~Visitor() = default;
};

#endif
#ifndef VISITOR_H
#define VISITOR_H
#include "../objects/camera.hpp"
#include "../objects/model.hpp"
#include "../objects/compositeObject.hpp"

class Visitor
{
    public:
        virtual void visit(Model &);
        virtual void visit(Camera &);
        virtual void visit(CompositeObject &); 
};

#endif
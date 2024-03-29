#include "compositeObject.hpp"

#include "../draw/visitor.h"
#include "objectType.hpp"

CompositeObject::CompositeObject()
{
    type = ObjectType::COMPOSITE;
}

ObjectType CompositeObject::getType() const 
{
    return type;
}

bool CompositeObject::add(std::shared_ptr<Object> obj)
{
    objects.add(obj);
    return true;
}

bool CompositeObject::remove(VectorIterator<std::shared_ptr<Object>>& it)
{
    objects.remove(it);
    return true;
}

void CompositeObject::transform(const Matrix<double> &transform_matrix)
{
    for (auto &obj : objects)
        obj->transform(transform_matrix);
}

VectorIterator<std::shared_ptr<Object>> CompositeObject::begin()
{
    return objects.begin();
}

VectorIterator<std::shared_ptr<Object>> CompositeObject::end()
{
    return objects.end();
}

void CompositeObject::accept(Visitor &visitor)
{
    for (auto obj : objects)
    {
        obj->accept(visitor);
    }
}

CompositeObject::~CompositeObject()
{
    for (auto &it : objects)
    {
        it.reset();
    }
    objects.reset();
}

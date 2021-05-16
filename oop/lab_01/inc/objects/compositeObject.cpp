#include "compositeObject.hpp"

bool CompositeObject::isVisible() const 
{
    return true;
}

bool CompositeObject::add(std::shared_ptr<Object> obj)
{
    objects.add(obj);
    return true;
}

bool CompositeObject::remove(VectorIterator<std::shared_ptr<Object>> it)
{
    objects.remove(it);
    return true;
}

bool CompositeObject::isComposite() const
{
    return true;
}

void CompositeObject::transform(std::shared_ptr<Matrix<double>> transform_matrix)
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
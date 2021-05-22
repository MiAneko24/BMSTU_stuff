#include "scene.hpp"

Scene::Scene()
{
    compositeObject.reset(new CompositeObject());
}

void Scene::add(std::shared_ptr<Object> object)
{
    compositeObject->add(std::move(object));
}

void Scene::remove(VectorIterator<std::shared_ptr<Object>> &it)
{
    compositeObject->remove(it);
}

VectorIterator<std::shared_ptr<Object>> Scene::getIterator(ObjectType type_obj, int index)
{
    bool flag = (type_obj == ObjectType::MODEL);
    int i = 0;
    auto it = compositeObject->begin();
    while (it != compositeObject->end() && i < index)
    {
        if (flag && (*it)->isVisible() || !(*it)->isVisible())
            i++;
        it++;
    }
    if (it == compositeObject->end() && i != index)
    {
        //throw error;
    }
    return it;
}

std::shared_ptr<Object> Scene::getObject(ObjectType type_obj, int index)
{
    return (*getIterator(type_obj, index));
}
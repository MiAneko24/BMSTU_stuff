#include "scene.hpp"

Scene::Scene()
{
    objects = Vector<std::shared_ptr<Object>>(1);
    objects[0] = std::shared_ptr<CompositeObject>(new CompositeObject());
}


void Scene::add(ObjectType type_obj, std::shared_ptr<Object> object, int curScene)
{
    if (type_obj == ObjectType::COMPOSITE)
    {
        objects.add(object);
    }
    else
    {
        objects[curScene]->add(object);
    }
}


VectorIterator<std::shared_ptr<Object>> Scene::getIterator(ObjectType type_obj, int index, int curScene)
{
    VectorIterator<std::shared_ptr<Object>> iter;
    if (type_obj != ObjectType::COMPOSITE)
    {
        bool flag_model = (type_obj == ObjectType::MODEL);
        int i = 0;
        VectorIterator<std::shared_ptr<Object>> it = objects[curScene]->begin();
        while (!it.isEnd())
        {
            if ((*it)->getType() == type_obj)
            {
                if (i == index)
                    break;
                i++;
            }
            it++;
        }
        if (it.isEnd())
        {
            time_t t_time = time(NULL);
            throw IndexError(ctime(&t_time), __FILE__, typeid(*this).name(), __LINE__, "Object's index is invalid");
        }
        iter = it;
    }
    else
    {
        int i = 0;
        VectorIterator<std::shared_ptr<Object>> it = objects.begin();
        while (!it.isEnd())
        {
            if (i == index)
                break;
            i++;
            it++;
        }
        if (it.isEnd())
        {
            time_t t_time = time(NULL);
            throw IndexError(ctime(&t_time), __FILE__, typeid(*this).name(), __LINE__, "Scene's index is invalid");
        }   
        iter = it;
    }
    return iter;
}

std::shared_ptr<Object> Scene::getObject(ObjectType type_obj, int index, int curScene)
{
    return (*getIterator(type_obj, index, curScene));
}


int Scene::getObjectsAmount(ObjectType type_obj, int curScene) {
    int amount = 0; 
    if (type_obj != ObjectType::COMPOSITE)
    {
        bool flag_model = (type_obj == ObjectType::MODEL);
        VectorIterator<std::shared_ptr<Object>> it = objects[curScene]->begin(); 
        while (!it.isEnd())
        {
            if ((*it)->getType() == type_obj)
            {
                amount++;
            }
            it++;
        }
    }
    else
    {
        VectorIterator<std::shared_ptr<Object>> it = objects.begin(); 
        while (!it.isEnd())
        {
            amount++;
            it++;
        }
    }
    return amount;
}

void Scene::remove(ObjectType type_obj, VectorIterator<std::shared_ptr<Object>> &it, int curScene)
{
    if (type_obj == ObjectType::COMPOSITE)
    {
        objects.remove(it);
        if (getObjectsAmount(type_obj, curScene) == 0)
            objects.add(std::shared_ptr<CompositeObject>(new CompositeObject()));
    }
    else
        objects[curScene]->remove(it);
}
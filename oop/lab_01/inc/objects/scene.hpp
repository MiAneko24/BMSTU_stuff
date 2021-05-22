#ifndef SCENE_CPP
#define SCENE_CPP

#include "object.hpp"
#include "compositeObject.hpp"
#include "objectType.hpp"

class Scene
{
    public:
        Scene();

        void add(std::shared_ptr<Object> obj);
        void remove(VectorIterator<std::shared_ptr<Object>> &it);
        VectorIterator<std::shared_ptr<Object>> getIterator(ObjectType type_obj, int index);
        std::shared_ptr<Object> getObject(ObjectType type_obj, int index);
        // std::shared_ptr<CompositeObject> getObject();

    private:
        std::shared_ptr<CompositeObject> compositeObject;
        
};

#endif
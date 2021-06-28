#ifndef SCENE_CPP
#define SCENE_CPP

#include "object.hpp"
#include "compositeObject.hpp"
#include "objectType.hpp"
#include "../base_elems/vector.hpp"
#include "../draw/visitor.h"

class Scene
{
    public:
        Scene();

        void add(ObjectType type_obj, std::shared_ptr<Object> obj, int curScene);
        void remove(ObjectType type_obj, VectorIterator<std::shared_ptr<Object>> &it, int curScene);
        VectorIterator<std::shared_ptr<Object>> getIterator(ObjectType type_obj, int index, int curScene);
 //       std::shared_ptr<Object> getObject(ObjectType type_obj, int index, int curScene);
        int getObjectsAmount(ObjectType type_obj, int curScene);

        ~Scene();
        
    private:
        Vector<std::shared_ptr<Object>> objects;
        
};

#endif
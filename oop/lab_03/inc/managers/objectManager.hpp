#ifndef OBJECTMANAGER_HPP
#define OBJECTMANAGER_HPP
#include "baseManager.hpp"
#include "../objects/scene.hpp"
#include "sceneManager.hpp"

class ObjectManager : public BaseManager
{
    public:
        ObjectManager(std::shared_ptr<SceneManager> manager);

        std::shared_ptr<Object> getObject(ObjectType type_obj);
        void addObject(ObjectType type_obj);
        void removeObject(ObjectType type_obj);
        void changeCurrentObject(ObjectType type_obj, int new_pos);
        void getObjectsAmount(ObjectType type_obj, int &amount);

        ~ObjectManager();
    private:
        std::shared_ptr<SceneManager> sceneManager;
};


#endif
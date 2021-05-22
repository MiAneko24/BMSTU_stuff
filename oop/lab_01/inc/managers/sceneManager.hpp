#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP

#include "baseManager.hpp"
#include "../objects/scene.hpp"

class SceneManager : public BaseManager
{
    public:
        SceneManager();

        std::shared_ptr<Object> getObject(ObjectType type_obj);
        // void addObject();
        void addObject(std::shared_ptr<Object> obj);
        void removeObject(ObjectType type_obj);
        void changeObject(ObjectType type_obj, int diff);
    private:
        Scene scene;
        int curCamera;
        int curModel;
};

#endif
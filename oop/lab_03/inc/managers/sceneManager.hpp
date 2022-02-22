#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP
#include "baseManager.hpp"
#include <memory>
#include "../objects/scene.hpp"

class SceneManager : public BaseManager
{
    public:
        SceneManager();

        std::shared_ptr<Scene> getScene();
        void addScene(std::shared_ptr<Object> new_scene);
        void removeScene();
        void setCurrentObjectPos(ObjectType type_obj, int pos);
        int getCurrentObjectPos(ObjectType type_obj);
        int getObjectsAmount(ObjectType type_obj);

        ~SceneManager();

    private:
        std::shared_ptr<Scene> scene;
        int curCamera;
        int curModel;
        int curScene;
};

#endif
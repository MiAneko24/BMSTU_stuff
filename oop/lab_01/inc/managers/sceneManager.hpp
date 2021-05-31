#ifndef SCENEMANAGER_HPP
#define SCENEMANAGER_HPP
#include "baseManager.hpp"
#include <memory>
#include "../objects/scene.hpp"

class SceneManager : public BaseManager
{
    public:
        std::shared_ptr<Scene> getScene();
        void setScene(std::shared_ptr<Scene> new_scene);
        void setCurrentObjectPos(ObjectType type_obj, int pos);
        int getCurrentObjectPos(ObjectType type_obj);

    private:
        std::shared_ptr<Scene> scene;
        int curCamera;
        int curModel;
};

#endif
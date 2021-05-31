#ifndef DRAWMANAGER_HPP
#define DRAWMANAGER_HPP

#include "baseManager.hpp"
#include <memory>
#include "sceneManager.hpp"
#include "../draw/drawer.h"

class DrawManager : public BaseManager, public Visitor
{
    public:
        DrawManager(std::shared_ptr<SceneManager> manager);
        void setDrawer(std::shared_ptr<Drawer> new_drawer);
        void drawModel();
        void visit(Model &model) override;
        void visit(Camera &camera) override;
        void visit(CompositeObject &composite) override;
    private:
        std::shared_ptr<Drawer> drawer;
        std::shared_ptr<SceneManager> sceneManager;
        std::shared_ptr<Camera> cam;
};

#endif
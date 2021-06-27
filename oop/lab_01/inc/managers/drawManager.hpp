#ifndef DRAWMANAGER_HPP
#define DRAWMANAGER_HPP

#include "baseManager.hpp"
#include <memory>
#include "sceneManager.hpp"
#include "../draw/drawer.h"
#include "../base_elems/connection.hpp"
#include "../base_elems/point.hpp"

class DrawManager : public BaseManager
{
    public:
        DrawManager(std::shared_ptr<SceneManager> manager);
        void setDrawer(std::shared_ptr<Drawer> new_drawer);
        void drawModel();
        ~DrawManager();
        
    private:
        std::shared_ptr<Drawer> drawer;
        std::shared_ptr<SceneManager> sceneManager;
};

#endif
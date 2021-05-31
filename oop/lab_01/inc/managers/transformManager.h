#ifndef TRANSFORMMANAGER_H
#define TRANSFORMMANAGER_H

#include "baseManager.hpp"
#include <memory>
#include "../objects/object.hpp"
#include "sceneManager.hpp"

class TransformManager : public BaseManager
{
    public:
        TransformManager(std::shared_ptr<SceneManager> manager);
        void move(ObjectType obj_type, Vector<double> &params);
        void scale(ObjectType obj_type, Vector<double> &params);
        void rotate(ObjectType obj_type, Vector<double> &params);
    
    private:
        std::shared_ptr<SceneManager> sceneManager;
};

#endif
#pragma once
#include <iostream>
#include <memory>
#include "../objects/objectType.hpp"
#include "../vector.hpp"
#include "../managers/objectManager.hpp"
#include "../managers/sceneManager.hpp"

class Controller
{
    public:
        static std::shared_ptr<Controller> getInstance();
        Controller(Controller &) = delete;
        Controller(const Controller &) = delete;
        Controller(Controller &&) = delete;
        ~Controller() = default;

        void addObject();
        void addObject(std::string file_name);
        void removeObject(ObjectType type_obj);
        void changeObject(ObjectType type_obj, int diff);

        void rotate(ObjectType type_object, Vector<double> &params);
        void move(ObjectType type_object, Vector<double> &params);
        void scale(ObjectType type_object, Vector<double> &params);

    private:
        Controller();
        static std::shared_ptr<Controller> sInstance;
        SceneManager sceneManager;
        ObjectManager ObjectManager;
        // std::shared_ptr<AbstractLoader> loader;

};
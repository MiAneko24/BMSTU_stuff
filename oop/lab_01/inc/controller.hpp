#pragma once
#include <iostream>
#include <memory>
#include "objectType.hpp"
#include "vector.hpp"

class Controller
{
    public:
        static std::shared_ptr<Controller> getInstance();
        Controller(Controller &) = delete;
        Controller(const Controller &) = delete;
        Controller(Controller &&) = delete;
        ~Controller() = default;

        void addModel(std::string model_name, std::string file_name);
        void addCamera(std::string cam_name);
        void setCamera(std::string cam_name);
        void removeModel(std::string model_name);
        void removeCamera(std::string cam_name);

        void rotate(ObjectType type_object, std::string name_object, Vector<double> &angles);
        void move(ObjectType type_object, std::string name_object, Vector<double> &move);
        void scale(ObjectType type_object, std::string name_object, Vector<double> &scale);

    private:
        Controller();
        SceneManager sceneManager;
        std::shared_ptr<AbstractLoader> loader;

};
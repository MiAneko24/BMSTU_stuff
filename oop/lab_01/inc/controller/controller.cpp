#include "controller.hpp"
#include "../objects/camera.hpp"

std::shared_ptr<Controller> Controller::getInstance()
{
    if (sInstance == nullptr)
        sInstance.reset(new Controller());
    return sInstance;
}

Controller::Controller() {};

void Controller::addObject()
{
    sceneManager.addObject(std::shared_ptr<Camera>(new Camera()));
}

void Controller::addObject(std::string filename)
{
    //load model
}

void Controller::removeObject(ObjectType type_obj)
{
    sceneManager.removeObject(type_obj);
}

void Controller::changeObject(ObjectType type_obj, int diff)
{
    sceneManager.changeObject(type_obj, diff);
}

void Controller::rotate(ObjectType type_obj, Vector<double> &params)
{
    auto obj = sceneManager.getObject(type_obj);
    ObjectManager.rotate(obj, params);
}

void Controller::move(ObjectType type_obj, Vector<double> &params)
{
    auto obj = sceneManager.getObject(type_obj);
    ObjectManager.move(obj, params);
}

void Controller::scale(ObjectType type_obj, Vector<double> &params)
{
    auto obj = sceneManager.getObject(type_obj);
    ObjectManager.scale(obj, params);
}


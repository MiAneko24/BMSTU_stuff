#pragma once
#include <iostream>
#include <memory>
#include "controller.hpp"

class BaseCommand
{
    public:
        BaseCommand() = default;
        ~BaseCommand() = default;

        virtual void execute(std::shared_ptr<Controller> controller) = 0;
};

class RotateCommand : public BaseCommand
{
    public:
        explicit RotateCommand(ObjectType type_obj, std::string object_name, Vector<double>& angles);
        void execute(std::shared_ptr<Controller> controller) override;
    
    private:
        ObjectType object_type; 
        std:: string name_object;
        Vector<double> rotate_params;
};


class MoveCommand : public BaseCommand
{
    public:
        explicit MoveCommand(ObjectType type_obj, std::string object_name, Vector<double> &move);
        void execute(std::shared_ptr<Controller> controller) override;
    
    private:
        ObjectType object_type; 
        std:: string name_object;
        Vector<double> move_params;
};


class ScaleCommand : public BaseCommand
{
    public:
        explicit ScaleCommand(ObjectType type_obj, std::string object_name, Vector<double> &scale);
        void execute(std::shared_ptr<Controller> controller) override;
    
    private:
        ObjectType object_type;
        std:: string name_object;
        Vector<double> scale_params;
};

class AddCameraCommand : public BaseCommand
{
    public:
        explicit AddCameraCommand(std::string name);
        void execute(std::shared_ptr<Controller> controller) override;
    
    private:
        std::string name_object;
};


class AddModelCommand : public BaseCommand
{
    public:
        explicit AddModelCommand(std::string name, std::string file);
        void execute(std::shared_ptr<Controller> controller) override;
    
    private:
        std::string name_object;
        std::string file_name;
};

class RemoveCommand : public BaseCommand
{
    public:
        explicit RemoveCommand(ObjectType type_obj, std::string name);
        void execute(std::shared_ptr<Controller> controller) override;
    
    private:
        ObjectType object_type; 
        std::string name_object;
};


class SetCameraCommand : public BaseCommand
{
    public:
        explicit SetCameraCommand(std::string name);
        void execute(std::shared_ptr<Controller> controller) override;
    
    private:
        std::string name_object;
};

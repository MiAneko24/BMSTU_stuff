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
        explicit RotateCommand(ObjectType type_obj, Vector<double>& angles);
        void execute(std::shared_ptr<Controller> controller) override;
    
    private:
        ObjectType object_type;
        Vector<double> rotate_params;
};


class MoveCommand : public BaseCommand
{
    public:
        explicit MoveCommand(ObjectType type_obj, Vector<double> &move);
        void execute(std::shared_ptr<Controller> controller) override;
    
    private:
        ObjectType object_type; 
        Vector<double> move_params;
};


class ScaleCommand : public BaseCommand
{
    public:
        explicit ScaleCommand(ObjectType type_obj, Vector<double> &scale);
        void execute(std::shared_ptr<Controller> controller) override;
    
    private:
        ObjectType object_type;
        Vector<double> scale_params;
};

class AddCameraCommand : public BaseCommand
{
    public:
        AddCameraCommand();
        void execute(std::shared_ptr<Controller> controller) override;
};


class AddModelCommand : public BaseCommand
{
    public:
        explicit AddModelCommand(std::string file);
        void execute(std::shared_ptr<Controller> controller) override;
    
    private:
        std::string file_name;
};

class RemoveCommand : public BaseCommand
{
    public:
        explicit RemoveCommand(ObjectType type_obj);
        void execute(std::shared_ptr<Controller> controller) override;
    
    private:
        ObjectType object_type;
};


class ChangeObjectCommand : public BaseCommand
{
    public:
        explicit ChangeObjectCommand(std::string name);
        void execute(std::shared_ptr<Controller> controller) override;
    
    private:
        std::string name_object;
};

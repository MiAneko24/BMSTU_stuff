#ifndef TRANSFORMCOMMANDS_HPP
#define TRANSFORMCOMMANDS_HPP
#include "../managers/transformManager.h"

#include "commands.hpp"

class RotateCommand : public BaseCommand
{
    private:
        ObjectType object_type;
        Vector<double> rotate_params;
        using Action = void (TransformManager::*)(ObjectType, Vector<double>);
        std::pair<std::shared_ptr<TransformManager>, Action> call;

    public:
        explicit RotateCommand(std::shared_ptr<TransformManager> manager, Action method, ObjectType type_obj, Vector<double>& angles);
        void execute() override;
};


class MoveCommand : public BaseCommand
{
    private:
        ObjectType object_type; 
        Vector<double> move_params;
        using Action = void (TransformManager::*)(ObjectType, Vector<double>);
        std::pair<std::shared_ptr<TransformManager>, Action> call;

    public:
        explicit MoveCommand(std::shared_ptr<TransformManager> manager, Action method, ObjectType type_obj, Vector<double> &move);
        void execute() override;
    
};


class ScaleCommand : public BaseCommand
{
    private:
        ObjectType object_type;
        Vector<double> scale_params;
        using Action = void (TransformManager::*)(ObjectType, Vector<double>);
        std::pair<std::shared_ptr<TransformManager>, Action> call;

    public:
        explicit ScaleCommand(std::shared_ptr<TransformManager> manager, Action method, ObjectType type_obj, Vector<double> &scale);
        void execute() override;
    
};



#endif
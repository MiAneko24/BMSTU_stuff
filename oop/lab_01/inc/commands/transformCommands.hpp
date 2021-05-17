#ifndef TRANSFORMCOMMANDS_HPP
#define TRANSFORMCOMMANDS_HPP
#include "commands.hpp"


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



#endif
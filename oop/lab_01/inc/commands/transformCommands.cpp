#include "transformCommands.hpp"

RotateCommand::RotateCommand(ObjectType type_obj, Vector<double> &angles)
{
    object_type = type_obj;
    rotate_params = angles;
}

void RotateCommand::execute(std::shared_ptr<Controller> controller)
{
    controller->rotate(object_type, rotate_params);
}


MoveCommand::MoveCommand(ObjectType type_obj, Vector<double> &move)
{
    object_type = type_obj;
    move_params = move;
}

void MoveCommand::execute(std::shared_ptr<Controller> controller)
{
    controller->move(object_type, move_params);
}

ScaleCommand::ScaleCommand(ObjectType type_obj, Vector<double> &scale)
{
    object_type = type_obj;
    scale_params = scale;
}

void ScaleCommand::execute(std::shared_ptr<Controller> controller)
{
    controller->scale(object_type, scale_params);
}

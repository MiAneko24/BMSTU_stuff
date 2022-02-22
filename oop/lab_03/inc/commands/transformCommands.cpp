#include "transformCommands.hpp"
#include "commands.hpp"

RotateCommand::RotateCommand(std::shared_ptr<TransformManager> manager, Action method, ObjectType type_obj, Vector<double>& angles) : object_type(type_obj), rotate_params(angles), call(manager, method) {};

void RotateCommand::execute()
{
    ((*call.first).*call.second)(object_type, rotate_params);
}
        

ScaleCommand::ScaleCommand(std::shared_ptr<TransformManager> manager, Action method, ObjectType type_obj, Vector<double>& scale) : object_type(type_obj), scale_params(scale), call(manager, method) {};

void ScaleCommand::execute()
{
    ((*call.first).*call.second)(object_type, scale_params);
}


MoveCommand::MoveCommand(std::shared_ptr<TransformManager> manager, Action method, ObjectType type_obj, Vector<double>& move) : object_type(type_obj), move_params(move), call(manager, method) {};

void MoveCommand::execute()
{
    ((*call.first).*call.second)(object_type, move_params);
}
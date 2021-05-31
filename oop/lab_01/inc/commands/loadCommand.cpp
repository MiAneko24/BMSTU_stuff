#include "commands.hpp"

LoadCommand::LoadCommand(std::shared_ptr<LoadManager> manager, Action method, ObjectType type_obj, std::string file) : call(manager, method), obj_type(type_obj), filename(file) {};

void LoadCommand::execute()
{
    ((*call.first).*call.second)(obj_type, filename);
}
#include "commands.hpp"

LoadCommand::LoadCommand(std::shared_ptr<LoadManager> manager, Action method, ObjectType type_obj, std::string file) : obj_type(type_obj), filename(file), call(manager, method) {};

void LoadCommand::execute()
{
    ((*call.first).*call.second)(obj_type, filename);
}
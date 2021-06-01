#include "objectCommands.hpp"
#include "commands.hpp"

RemoveCommand::RemoveCommand(std::shared_ptr<ObjectManager> manager, Action method, ObjectType type_obj) : object_type(type_obj), call(manager, method) {};

void RemoveCommand::execute()
{
    ((*call.first).*call.second)(object_type);
}


ChangeObjectCommand::ChangeObjectCommand(std::shared_ptr<ObjectManager> manager, Action method, ObjectType type_obj, int diff) : object_type(type_obj), change(diff), call(manager, method) {}

void ChangeObjectCommand::execute()
{
    ((*call.first).*call.second)(object_type, change);
}

AddObjectCommand::AddObjectCommand(std::shared_ptr<ObjectManager> manager, Action method, ObjectType type_obj) : object_type(type_obj), call(manager, method) {};

void AddObjectCommand::execute()
{
    ((*call.first).*call.second)(object_type);
}

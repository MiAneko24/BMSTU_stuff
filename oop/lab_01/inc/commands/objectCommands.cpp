#include "objectCommands.hpp"
#include "commands.hpp"

RemoveCommand::RemoveCommand(std::shared_ptr<ObjectManager> manager, Action method, ObjectType type_obj) : call(manager, method), object_type(type_obj) {};

void RemoveCommand::execute()
{
    ((*call.first).*call.second)(object_type);
}


ChangeObjectCommand::ChangeObjectCommand(std::shared_ptr<ObjectManager> manager, Action method, ObjectType type_obj, int diff) : call(manager, method), object_type(type_obj), change(diff) {}

void ChangeObjectCommand::execute()
{
    ((*call.first).*call.second)(object_type, change);
}

AddObjectCommand::AddObjectCommand(std::shared_ptr<ObjectManager> manager, Action method, ObjectType type_obj) : call(manager, method), object_type(type_obj) {};

void AddObjectCommand::execute()
{
    ((*call.first).*call.second)(object_type);
}

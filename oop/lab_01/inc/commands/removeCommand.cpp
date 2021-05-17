#include "removeCommand.hpp"

RemoveCommand::RemoveCommand(ObjectType type_obj)
{
    object_type = type_obj;
}

void RemoveCommand::execute(std::shared_ptr<Controller> controller)
{
    controller->removeObject(object_type);
}
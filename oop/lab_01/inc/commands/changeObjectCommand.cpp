#include "changeObjectCommand.hpp"

ChangeObjectCommand::ChangeObjectCommand(ObjectType type_obj, int diff)
{
    object_type = type_obj;
    change = diff;
}

void ChangeObjectCommand::execute(std::shared_ptr<Controller> controller)
{
    controller->changeObject(object_type, change);
}
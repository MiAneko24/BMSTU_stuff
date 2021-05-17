#include "addCommands.hpp"

void AddCameraCommand::execute(std::shared_ptr<Controller> controller)
{
    controller->addObject();
}

AddModelCommand::AddModelCommand(std::string file) : file_name(file) {};

void AddModelCommand::execute(std::shared_ptr<Controller> controller)
{
    controller->addObject(file_name);
}
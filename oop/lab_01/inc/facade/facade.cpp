#include "facade.hpp"

Facade::Facade()
{
    controller = Controller::getInstance();
}

void Facade::execute(std::shared_ptr<BaseCommand> command)
{
    command->execute(controller);
}

Facade::~Facade()
{
    controller.reset();
}
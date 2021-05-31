#include "facade.hpp"


void Facade::execute(std::shared_ptr<BaseCommand> command)
{
    command->execute();
}

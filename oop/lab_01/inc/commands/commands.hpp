#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include <memory>
#include "../objects/objectType.hpp"
#include "../vector.hpp"
#include "../controller/controller.hpp"

class BaseCommand
{
    public:
        BaseCommand() = default;
        ~BaseCommand() = default;

        virtual void execute(std::shared_ptr<Controller> controller) = 0;
};

#include "addCommands.hpp"
#include "removeCommand.hpp"
#include "changeObjectCommand.hpp"
#include "transformCommands.hpp"

#endif
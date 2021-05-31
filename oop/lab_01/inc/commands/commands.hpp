#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include <memory>
#include "../objects/objectType.hpp"
#include "../vector.hpp"

class BaseCommand
{
    public:
        BaseCommand() = default;
        ~BaseCommand() = default;

        virtual void execute() = 0;
};

#include "loadCommand.hpp"
#include "objectCommands.hpp"
#include "transformCommands.hpp"
#include "drawCommand.h"

#endif
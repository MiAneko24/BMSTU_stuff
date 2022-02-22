#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include <memory>
#include "../objects/objectType.hpp"
#include "../base_elems/vector.hpp"

class BaseCommand
{
    public:
        virtual void execute() = 0;
        virtual ~BaseCommand() = default;
};

#include "loadCommand.hpp"
#include "objectCommands.hpp"
#include "transformCommands.hpp"
#include "drawCommand.h"

#endif
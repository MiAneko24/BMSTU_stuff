#ifndef FACADE_HPP
#define FACADE_HPP
#include "../commands/commands.hpp"

class Facade
{
    public:
        Facade();
        
        void execute(std::shared_ptr<BaseCommand> command);
        
        ~Facade();
};

#endif
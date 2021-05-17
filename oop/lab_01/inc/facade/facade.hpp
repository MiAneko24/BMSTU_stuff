#ifndef FACADE_HPP
#define FACADE_HPP
#include "../commands.hpp"
#include "../controller/controller.hpp"

class Facade
{
    public:
        Facade();
        
        void execute(std::shared_ptr<BaseCommand> command);
        
        ~Facade();

    private:
        std::shared_ptr<Controller> controller;
};

#endif
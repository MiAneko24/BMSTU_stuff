#ifndef REMOVECOMMAND_HPP
#define REMOVECOMMAND_HPP
#include "commands.hpp"

class RemoveCommand : public BaseCommand
{
    public:
        explicit RemoveCommand(ObjectType type_obj);
        void execute(std::shared_ptr<Controller> controller) override;
    
    private:
        ObjectType object_type;
};


#endif
#ifndef CHANGEOBJECTCOMMAND_HPP
#define CHANGEOBJECTCOMMAND_HPP
#include "commands.hpp"

class ChangeObjectCommand : public BaseCommand
{
    public:
        explicit ChangeObjectCommand(ObjectType type_obj, int diff);
        void execute(std::shared_ptr<Controller> controller) override;
};


#endif
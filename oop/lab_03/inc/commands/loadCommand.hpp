#ifndef LOADCOMMAND_HPP
#define LOADCOMMAND_HPP
#include "../managers/loadManager.hpp"

#include "commands.hpp"

class LoadCommand : public BaseCommand
{
    private:
        ObjectType obj_type;
        std::string filename;
        using Action = void (LoadManager::*)(ObjectType, std::string);
        std::pair<std::shared_ptr<LoadManager>, Action> call;

    public:
        LoadCommand(std::shared_ptr<LoadManager> manager, Action method, ObjectType type_obj, std::string file);
        void execute() override;
        ~LoadCommand() = default;
};


#endif
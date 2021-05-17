#ifndef ADDCOMMANDS_HPP
#define ADDCOMMANDS_HPP
#include "commands.hpp"


class AddCameraCommand : public BaseCommand
{
    public:
        AddCameraCommand();
        void execute(std::shared_ptr<Controller> controller) override;
};


class AddModelCommand : public BaseCommand
{
    public:
        explicit AddModelCommand(std::string file);
        void execute(std::shared_ptr<Controller> controller) override;
    
    private:
        std::string file_name;
};


#endif
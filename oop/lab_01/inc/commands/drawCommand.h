#ifndef DRAWCOMMAND_H
#define DRAWCOMMAND_H
#include "../managers/drawManager.hpp"
#include "commands.hpp"

class DrawCommand : public BaseCommand
{
    private:
        using Action = void (DrawManager::*)();
        std::pair<std::shared_ptr<DrawManager>, Action> call;

    public:
        DrawCommand(std::shared_ptr<DrawManager> manager, Action method);
        void execute() override;
};



#endif
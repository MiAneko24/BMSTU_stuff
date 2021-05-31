#include "commands.hpp"


DrawCommand::DrawCommand(std::shared_ptr<DrawManager> manager, Action method) : call(manager, method) {};

void DrawCommand::execute()
{
    ((*call.first).*call.second)();
}
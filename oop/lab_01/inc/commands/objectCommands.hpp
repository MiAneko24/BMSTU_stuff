#ifndef OBJECTCOMMANDS_HPP
#define OBJECTCOMMANDS_HPP
#include "../managers/objectManager.hpp"
#include "commands.hpp"

class RemoveCommand : public BaseCommand
{
    private:
        ObjectType object_type;
        using Action = void (ObjectManager::*)(ObjectType);
        std::pair<std::shared_ptr<ObjectManager>, Action> call;
    
    public:
        explicit RemoveCommand(std::shared_ptr<ObjectManager> manager, Action method, ObjectType type_obj);
        void execute() override;
};

class ChangeObjectCommand : public BaseCommand
{
    private:
        ObjectType object_type;
        int change;
        using Action = void (ObjectManager::*)(ObjectType, int);
        std::pair<std::shared_ptr<ObjectManager>, Action> call;
    
    public:
        explicit ChangeObjectCommand(std::shared_ptr<ObjectManager> manager, Action method, ObjectType type_obj, int diff);
        void execute() override;
};

class AddObjectCommand : public BaseCommand
{
    private:
        ObjectType object_type;
        using Action = void (ObjectManager::*)(ObjectType);
        std::pair<std::shared_ptr<ObjectManager>, Action> call;
    
    public:
        explicit AddObjectCommand(std::shared_ptr<ObjectManager> manager, Action method, ObjectType type_obj);
        void execute() override;
};


#endif
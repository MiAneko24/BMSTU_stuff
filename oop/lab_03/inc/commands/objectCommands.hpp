#ifndef OBJECTCOMMANDS_HPP
#define OBJECTCOMMANDS_HPP
#include "../managers/objectManager.hpp"
#include "commands.hpp"

class RemoveObjectCommand : public BaseCommand
{
    private:
        ObjectType object_type;
        using Action = void (ObjectManager::*)(ObjectType);
        std::pair<std::shared_ptr<ObjectManager>, Action> call;
    
    public:
        explicit RemoveObjectCommand(std::shared_ptr<ObjectManager> manager, Action method, ObjectType type_obj);
        void execute() override;
        ~RemoveObjectCommand() = default;
};

class GetAmountCommand : public BaseCommand
{
    private:
        ObjectType object_type;
        int& amount;
        using Action = void (ObjectManager::*)(ObjectType, int&);
        std::pair<std::shared_ptr<ObjectManager>, Action> call;
    
    public:
        explicit GetAmountCommand(std::shared_ptr<ObjectManager> manager, Action method, ObjectType type_obj, int& num);
        void execute() override;
        ~GetAmountCommand() = default;
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
        ~ChangeObjectCommand() = default;
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
        ~AddObjectCommand() = default;
};


#endif
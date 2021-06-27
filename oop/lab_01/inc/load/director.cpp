#include "director.h"
#include "modelBuilder.h"
#include "compositeBuilder.h"
#include "cameraBuilder.h"
#include "../objects/scene.hpp"

std::shared_ptr<Object> Director::create(ObjectType type_obj, std::shared_ptr<BaseBuilder> builder, std::ifstream& file)
{
    std::shared_ptr<Object> obj = nullptr;
    switch (type_obj)
    {
        case ObjectType::MODEL:
            if (builder->buildModel(file))
                obj = builder->getObject();
            break;
        case ObjectType::CAMERA:
            if (builder->buildCamera(file))
                obj = builder->getObject();
            break;
        case ObjectType::COMPOSITE:
            if (builder->buildModel(file) && builder->buildCamera(file))
                obj = builder->getObject();
            break;
        default:
            break;
    }
    return obj;
}

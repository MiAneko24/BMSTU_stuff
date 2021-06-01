#include "director.h"
#include "modelBuilder.h"
#include "sceneBuilder.h"
#include "cameraBuilder.h"

std::shared_ptr<Object> Director::create(ObjectType type_obj, std::shared_ptr<BaseBuilder> builder, std::ifstream& file)
{
    std::shared_ptr<Object> obj = nullptr;
    if (builder->buildModel(file) && builder->buildCamera(file))
        obj = builder->getObject();
    return obj;
}

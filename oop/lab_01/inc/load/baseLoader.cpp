#include "baseLoader.hpp"

BaseLoader::BaseLoader()
{
    director.reset(new Director());
}

void BaseLoader::open(std::string filename)
{
    file.open(filename);
    if (!file)
    {
        // throw
    }
}

void BaseLoader::close()
{
    file.close();
}

std::shared_ptr<Object> BaseLoader::loadModel(ObjectType type_obj, std::string filename)
{
    open(filename);
    std::shared_ptr<BaseBuilder> builder;
    if (type_obj == ObjectType::CAMERA)
        builder.reset(new CameraBuilder());
    else if (type_obj == ObjectType::MODEL)
        builder.reset(new ModelBuilder());
    else
        builder.reset(new SceneBuilder());
    std::shared_ptr<Object> obj = director->create(type_obj, builder, file);
    close();
    return obj;
}
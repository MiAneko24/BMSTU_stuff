#include "baseLoader.hpp"
#include "../base_elems/exceptions.hpp"

BaseLoader::BaseLoader()
{
    director.reset(new Director());
}

void BaseLoader::open(std::string filename)
{
    if (file.is_open())
        close();

    file.open(filename);
    time_t t_time = time(NULL);
    if (!file)
    {
        throw FileOpenError(ctime(&t_time), __FILE__, typeid(*this).name(), __LINE__);
    }
}

void BaseLoader::close()
{
    if (file.is_open())
        file.close();
}

std::shared_ptr<Object> BaseLoader::loadObject(ObjectType type_obj, std::string filename)
{
    open(filename);
    std::shared_ptr<BaseBuilder> builder;
    if (type_obj == ObjectType::CAMERA)
    {
        builder.reset(new CameraBuilder());
    }
    else if (type_obj == ObjectType::MODEL)
    {
        builder.reset(new ModelBuilder());
    }
    else
    {
        builder.reset(new CompositeBuilder());    
    }
    std::shared_ptr<Object> obj = nullptr;
    try
    {
        obj = director->create(type_obj, builder, file);
    }
    catch(FileDataError &e)
    {
        std::cerr << e.what() << '\n';
        close();
        throw e;
    }
    
    close();
    return obj;
}
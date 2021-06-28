#include "director.h"
#include "modelBuilder.h"
#include "compositeBuilder.h"
#include "cameraBuilder.h"
#include "../objects/scene.hpp"

std::shared_ptr<Object> Director::create(ObjectType type_obj, std::shared_ptr<BaseBuilder> builder, std::ifstream& file)
{
    std::shared_ptr<Object> obj = nullptr;
    // switch (type_obj)
    // {
    //     case ObjectType::MODEL:
    //         if (builder->buildModel(file))
    //             obj = builder->getObject();
    //         break;
    //     case ObjectType::CAMERA:
    //         if (builder->buildCamera(file))
    //             obj = builder->getObject();
    //         break;
    //     case ObjectType::COMPOSITE:
    //         if (builder->buildModel(file) && builder->buildCamera(file))
    //             obj = builder->getObject();
    //         break;
    //     default:
    //         break;
    // }
    return obj;
}

void Director::setLoader(std::shared_ptr<BaseLoader> load)
{
    loader = load;
}

std::shared_ptr<Object> Director::create(ObjectType type_obj, std::shared_ptr<BaseBuilder> builder, std::string filename)
{
    loader->open(filename);
    std::shared_ptr<Object> obj = nullptr;
    switch (type_obj)
    {
    case ObjectType::MODEL:
        createModel(builder);
        break;
    case ObjectType::COMPOSITE:
        createComposite(builder);
    default:
        break;
    }
    loader->close();
    return builder->getObject();
}

void Director::createModel(std::shared_ptr<BaseBuilder> builder)
{
    int amount = loader->loadAmount();
    Vector<Point> points;
    for (int i = 0; i < amount; i++)
    {
        Point point = loader->loadPoint();
        points.add(point);
    }
    builder->buildPoints(points);
    amount = loader->loadAmount();
    Vector<Connection> connections;
    for (int i = 0; i < amount; i++)
    {
        Connection connection = loader->loadConnection();
        connections.add(connection);
    }
    builder->buildConnections(connections);
    builder->buildModel();
    // if (builder->buildModel())
    //     obj = builder->getObject();
    // return obj;
}

void Director::createCamera(std::shared_ptr<BaseBuilder> builder)
{
    Point point = loader->loadPoint();
    builder->buildPosition(point);
    Vector<double> vect = loader->loadAngles();
    builder->buildAngles(vect);
    builder->buildCamera();
}

void Director::createComposite(std::shared_ptr<BaseBuilder> builder)
{
    int amount = loader->loadAmount();
    for (int i = 0; i < amount; i++)
    {
        createModel(builder);
    }
    amount = loader->loadAmount();
    for (int i = 0; i < amount; i++)
    {
        createCamera(builder);
    }
}

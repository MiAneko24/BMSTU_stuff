#include "director.h"
#include "modelBuilder.h"
#include "compositeBuilder.h"
#include "cameraBuilder.h"
#include "../objects/scene.hpp"


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
    if (builder->isBuilt())
        obj = builder->getObject();
    return obj;
}

void Director::createModel(std::shared_ptr<BaseBuilder> builder)
{
    int amount = loader->loadAmount();
    Vector<Point> points;
    for (int i = 0; i < amount; i++)
    {
        points.add(loader->loadPoint());
    }
    builder->buildPoints(points);
    amount = loader->loadAmount();
    Vector<Connection> connections;
    for (int i = 0; i < amount; i++)
    {
        connections.add(loader->loadConnection());
    }
    builder->buildConnections(connections);
    builder->buildModel();
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

#include "modelBuilder.h"
#include "../objects/model.hpp"
#include "../base_elems/point.hpp"
#include "../base_elems/connection.hpp"
#include "../objects/frameModel.h"

bool ModelBuilder::buildModel(std::ifstream& file)
{
    frame.reset(new FrameModel());
    bool flag = buildPoints(file) && buildConnections(file);
    if (flag)
        object.reset(new Model(frame));
    return flag;
}

bool ModelBuilder::buildPoints(std::ifstream &file)
{
    bool state = true;
    int amount = 0;
    Vector<Point> points;
    if (!(file >> amount && amount > 0))
    {
        time_t t_time = time(NULL);
        throw FileDataError(ctime(&t_time), __FILE__, typeid(*this).name(), __LINE__);
    }
    for (int i = 0; i < amount && state; i++)
    {
        double x, y, z;
        if (file >> x >> y >> z)
        {
            points.add(Point(x, y, z));
        }
        else
        {
            time_t t_time = time(NULL);
            throw FileDataError(ctime(&t_time), __FILE__, typeid(*this).name(), __LINE__);
        }
    }
    std::shared_ptr<Model> model = std::dynamic_pointer_cast<Model>(object);
    frame->fill(points);
    return state;
}


bool ModelBuilder::buildConnections(std::ifstream &file)
{
    bool state = true;
    int amount = 0;
    Vector<Connection> connections;
    if (!(file >> amount && amount > 0))
    {
        time_t t_time = time(NULL);
        throw FileDataError(ctime(&t_time), __FILE__, typeid(*this).name(), __LINE__);
    }
    for (int i = 0; i < amount && state; i++)
    {
        int first, second;
        if (file >> first >> second)
        {
            connections.add(Connection(first, second));
        }
        else
        {
            time_t t_time = time(NULL);
            throw FileDataError(ctime(&t_time), __FILE__, typeid(*this).name(), __LINE__);
        }
    }
    std::shared_ptr<Model> model = std::dynamic_pointer_cast<Model>(object);
    frame->fill(connections);
    return state;
}

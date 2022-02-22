#include "modelBuilder.h"
#include "../objects/model.hpp"
#include "../base_elems/point.hpp"
#include "../base_elems/connection.hpp"
#include "../objects/frameModel.h"

ModelBuilder::ModelBuilder()
{
    builtParts = 0;
    frame.reset(new FrameModel());
}

bool ModelBuilder::buildModel()
{
    object.reset(new Model(frame));
    return true;
}

bool ModelBuilder::buildPoints(Vector<Point> &points)
{
    builtParts++;
    bool state = true;
    Vector<Point> tmp = points;
    frame->fill(tmp);
    return state;
}


bool ModelBuilder::buildConnections(Vector<Connection> &connection)
{
    builtParts++;
    bool state = true;
    frame->fill(connection);
    return state;
}

bool ModelBuilder::isBuilt()
{
    if (builtParts == 2)
        return true;
    return false;
}
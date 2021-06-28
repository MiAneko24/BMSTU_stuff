#include "modelBuilder.h"
#include "../objects/model.hpp"
#include "../base_elems/point.hpp"
#include "../base_elems/connection.hpp"
#include "../objects/frameModel.h"

bool ModelBuilder::buildModel()
{
    frame.reset(new FrameModel());
    object.reset(new Model(frame));
    return true;
}

bool ModelBuilder::buildPoints(Vector<Point> &points)
{
    bool state = true;
    frame->fill(points);
    return state;
}


bool ModelBuilder::buildConnections(Vector<Connection> &connection)
{
    bool state = true;
    frame->fill(connection);
    return state;
}

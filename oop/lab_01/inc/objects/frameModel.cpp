#include "frameModel.h"

const Vector<Point> FrameModel::getPoints()
{
    return points;
}

const Vector<Connection> FrameModel::getConnections()
{
    return connections;
}

void FrameModel::fill(Vector<Point> &new_points)
{
    points = Vector<Point>(new_points);
}

void FrameModel::fill(Vector<Connection> &new_connections)
{
    connections = new_connections;
}

void FrameModel::transform(const Matrix<double> &transform_matrix)
{
    for (size_t i = 0; i < points.getSize(); i++)
        points[i].transform(transform_matrix);
}

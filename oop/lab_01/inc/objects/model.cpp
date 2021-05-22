#include "model.hpp"

Model::Model(const Model &model) : points(model.points), connections(model.connections) {};

Model::Model(Model &&model) noexcept : points(model.points), connections(model.connections) {};

bool Model::isVisible() const
{
    return true;
}

Model& Model::operator =(const Model& model)
{
    if (this != &model)
    {
        points = model.points;
        connections = model.connections;
    }
    return *this;
}

Model& Model::operator =(const Model& model) noexcept
{
    if (this != &model)
    {
        points = model.points;
        connections = model.connections;
    }
    return *this;
}

const Vector<Point> Model::getPoints()
{
    return points;
}

const Vector<Connection> Model::getConnections()
{
    return connections;
}

void Model::transform(const Matrix<double> &transform_matrix)
{
    for (size_t i = 0; i < points.getSize(); i++)
        points[i].transform(transform_matrix);
}

void Model::fill(const Vector<Point> &new_points)
{
    points = new_points;
}

void Model::fill(const Vector<Connection> &new_connections)
{
    connections = new_connections;
}

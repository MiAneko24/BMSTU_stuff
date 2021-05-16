#include "model.hpp"

Model::Model(const Model &model) : points(model.points), connections(model.connections) {};

Model::Model(Model &&model) noexcept : points(model.points), connections(model.connections) {};

bool Model::isVisible()
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

Vector<Point> Model::getPoints()
{
    return points;
}

Vector<Connection> Model::getConnections()
{
    return connections;
}

void Model::transform(const Matrix<double> &transformation_matrix)
{
    for (size_t i = 0; i < points.getSize(); i++)
        points[i].transform(transformation_matrix);
}

void Model::fill(const Vector<Point> &new_points)
{
    points = new_points;
}

void Model::fill(const Vector<Connection> &new_connections)
{
    connections = new_connections;
}

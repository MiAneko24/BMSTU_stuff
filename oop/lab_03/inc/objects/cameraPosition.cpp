#include "cameraPosition.h"
#include "../base_elems/matrix.hpp"

CameraPosition::CameraPosition()
{
    position = Point(0, 0, 300);
    angles = Vector<double>({0, 0, 0}, 3);
}

const Point& CameraPosition::getPosition() const
{
    return position;
}

double CameraPosition::getXAngle() const
{
    return angles[0];
}

void CameraPosition::setPosition(Point position)
{
    this->position = position;
}

double CameraPosition::getYAngle() const
{
    return angles[1];
}

double CameraPosition::getZAngle() const
{
    return angles[2];
}

void CameraPosition::setAngles(const Vector<double> &params)
{
    for (int i = 0; i < 3; i++)
    {
        angles[i] += params[i];
    }
}

void CameraPosition::transform(const Matrix<double> &mat)
{
    position.transform(mat);
}

Point CameraPosition::getProjection(Point& point)
{
    Matrix<double> move_mat = Matrix<double>(4, 4);
    Vector<double> params = Vector<double>({-position.getX(), -position.getY(), 0}, 3);
    Vector<double> vect_point = point.toVector();
    move_mat.make_move_matrix(params);
    vect_point *= move_mat;
    params = {-angles[0], -angles[1], -angles[2]};
    move_mat.make_rotate_matrix(params);
    vect_point *= move_mat;
    Point res;
    res.setFromVector(vect_point);
    return res;
}
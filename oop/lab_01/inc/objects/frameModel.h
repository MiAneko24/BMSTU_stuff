#ifndef FRAMEMODEL_H
#define FRAMEMODEL_H
#include "../point.hpp"
#include "../connection.hpp"
#include "../vector.hpp"

class FrameModel
{
    public:
        const Vector<Point> getPoints();
        const Vector<Connection> getConnections();
        void fill(Vector<Point> &new_points);
        void fill(Vector<Connection> &new_connections);
        void transform(const Matrix<double>& transform_matrix);
        
    private:
        Vector<Point> points;
        Vector<Connection> connections;
        
};

#endif
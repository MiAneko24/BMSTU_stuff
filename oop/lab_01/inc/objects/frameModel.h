#ifndef FRAMEMODEL_H
#define FRAMEMODEL_H
#include "../base_elems/point.hpp"
#include "../base_elems/connection.hpp"
#include "../base_elems/vector.hpp"

class FrameModel
{
    public:
        FrameModel() = default;
        const Vector<Point> getPoints();
        const Vector<Connection> getConnections();
        void fill(Vector<Point> &new_points);
        void fill(Vector<Connection> &new_connections);
        void transform(const Matrix<double>& transform_matrix);

        ~FrameModel() = default;
        
    private:
        Vector<Point> points = Vector<Point>();
        Vector<Connection> connections = Vector<Connection>();
        
};

#endif
#ifndef MODEL_HPP
#define MODEL_HPP

#include "vector.hpp"
#include "matrix.hpp"
#include "point.hpp"
#include "object.hpp"
#include "connection.hpp"
class Model : public Object
{
    public:
        Model() = default;
        Model(const Model &);
        Model(Model &&) noexcept;
        ~Model() = default;

        bool isVisible();

        Model& operator =(const Model&);
        Model& operator =(Model &&) noexcept;

        Vector<Point> getPoints();
        Vector<Connection> getConnections();
        void transform(const Matrix<double> &transformation_matrix);
        void fill(const Vector<Point>& points);
        void fill(const Vector<Connection> &connections);

    private:
        Vector<Point>& points;
        Vector<Connection>& connections;
};

#endif
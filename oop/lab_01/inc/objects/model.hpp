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

        bool isVisible() const override;

        Model& operator =(const Model&);
        Model& operator =(Model &&) noexcept;

        const Vector<Point> getPoints();
        const Vector<Connection> getConnections();
        void transform(const Matrix<double> &transform_matrix) override;
        void fill(const Vector<Point>& points);
        void fill(const Vector<Connection> &connections);

    private:
        Vector<Point> points;
        Vector<Connection> connections;
};

#endif
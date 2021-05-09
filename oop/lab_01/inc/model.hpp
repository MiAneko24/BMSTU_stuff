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
        explicit Model(std::string name);
        Model(const Model &);
        Model(Model &&) noexcept;
        ~Model() = default;

        bool isVisible() const final;

        Model& operator =(const Model&);
        Model& operator =(Model &&) noexcept;

        Vector<Point>& getPoints();
        Vector<Connection>& getConnections();
        void transform(const std::shared_ptr<Matrix<double>> transformation_matrix);
        void add(const Vector<Point>& points);
        void add(const Vector<Connection> &connections);

    private:
        Vector<Point> points;
        Vector<Connection> connections;
};

#endif
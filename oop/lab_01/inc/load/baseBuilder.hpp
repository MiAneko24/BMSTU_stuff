#ifndef BASEBUILDER_HPP
#define BASEBUILDER_HPP
#include <memory>
#include "../objects/object.hpp"
#include <fstream>
#include "../objects/objectType.hpp"
#include "../base_elems/point.hpp"
#include "../base_elems/connection.hpp"

class BaseBuilder
{
    public:
        virtual bool buildModel();
        virtual bool buildCamera();
        virtual bool buildPoints(Vector<Point> &points);
        virtual bool buildAngles(Vector<double> &angles);
        virtual bool buildPosition(Point &pos);
        virtual bool buildConnections(Vector<Connection> &connections);
        // virtual bool isBuilt() = 0;
        std::shared_ptr<Object> getObject();
        virtual ~BaseBuilder() = 0;

    protected:
        std::shared_ptr<Object> object;
};

#endif
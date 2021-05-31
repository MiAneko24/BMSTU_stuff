#ifndef MODELBUILDER_H
#define MODELBUILDER_H
#include "baseBuilder.hpp"
#include "../point.hpp"
#include "../connection.hpp"
#include "../vector.hpp"

class ModelBuilder : public BaseBuilder
{
    public:
        bool buildModel(std::ifstream& file) override;
        bool buildPoints(std::ifstream& file);
        bool buildConnections(std::ifstream& file);
    
    private:
        Vector<Point> points;
        Vector<Connection> connections;
};

#endif
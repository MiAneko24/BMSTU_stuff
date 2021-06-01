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
        bool buildCamera(std::ifstream& file) override;
        
    private:
        bool buildPoints(std::ifstream& file);
        bool buildConnections(std::ifstream& file);
};

#endif
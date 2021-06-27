#ifndef MODELBUILDER_H
#define MODELBUILDER_H
#include "baseBuilder.hpp"
#include "../base_elems/point.hpp"
#include "../base_elems/connection.hpp"
#include "../base_elems/vector.hpp"

class ModelBuilder : public BaseBuilder
{
    public:
        bool buildModel(std::ifstream& file) override;
        bool buildCamera(std::ifstream& file) override;
        ~ModelBuilder() = default;
        
    private:
        bool buildPoints(std::ifstream& file);
        bool buildConnections(std::ifstream& file);
};

#endif
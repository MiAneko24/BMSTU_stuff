#ifndef BASEBUILDER_HPP
#define BASEBUILDER_HPP
#include <memory>
#include "../objects/object.hpp"
#include <fstream>
#include "../objects/objectType.hpp"

class BaseBuilder
{
    public:
        virtual bool buildModel(std::ifstream&) = 0;
        virtual bool buildCamera(std::ifstream&) = 0;
        std::shared_ptr<Object> getObject();

    protected:
        std::shared_ptr<Object> object;
};

#endif
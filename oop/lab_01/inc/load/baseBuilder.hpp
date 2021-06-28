#ifndef BASEBUILDER_HPP
#define BASEBUILDER_HPP
#include <memory>
#include "../objects/object.hpp"
#include <fstream>
#include "../objects/objectType.hpp"

class BaseBuilder
{
    public:
        virtual bool buildModel(std::ifstream&);
        virtual bool buildCamera(std::ifstream&);
        std::shared_ptr<Object> getObject();
        virtual ~BaseBuilder() = 0;

    protected:
        std::shared_ptr<Object> object;
};

#endif
#ifndef DIRECTOR_H
#define DIRECTOR_H
#include "baseBuilder.hpp"

class Director
{
    public:
        Director() = default;
        std::shared_ptr<Object> create(ObjectType, std::shared_ptr<BaseBuilder>, std::ifstream& file);

};


#endif
#ifndef DIRECTOR_H
#define DIRECTOR_H
#include "baseBuilder.hpp"
#include "cameraBuilder.h"
#include "modelBuilder.h"
#include "sceneBuilder.h"

class Director
{
    public:
        Director() = default;
        std::shared_ptr<Object> create(ObjectType, std::shared_ptr<BaseBuilder>, std::ifstream& file);

};


#endif
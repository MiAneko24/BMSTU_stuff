#pragma once

#include <iostream>
#include <memory>
#include <fstream>
#include "../vector.hpp"
#include "../point.hpp"
#include "director.h"
#include "cameraBuilder.h"
#include "modelBuilder.h"
#include "sceneBuilder.h"

class BaseLoader
{
    public:
        BaseLoader();
        ~BaseLoader();
        void open(std::string filename);
        std::shared_ptr<Object> loadModel(ObjectType type_obj, std::string file);
        void close();
        
    private:
        std::ifstream file;
        std::shared_ptr<Director> director;
};

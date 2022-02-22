#pragma once

#include <iostream>
#include <memory>
#include <fstream>
#include "../base_elems/vector.hpp"
#include "../base_elems/point.hpp"
#include "../base_elems/connection.hpp"
#include "cameraBuilder.h"
#include "modelBuilder.h"
#include "compositeBuilder.h"

class BaseLoader
{
    public:
        BaseLoader();
        void open(std::string filename);
        Point loadPoint();
        Connection loadConnection();
        Vector<double> loadAngles();
        int loadAmount();
        void close();
        virtual ~BaseLoader() = default;
        
    private:
        std::ifstream file;
};

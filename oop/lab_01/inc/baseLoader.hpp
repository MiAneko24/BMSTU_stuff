#pragma once

#include <iostream>
#include <memory>
#include <fstream>
#include "vector.hpp"
#include "point.hpp"

class BaseModelLoader
{
    public:
        virtual ~BaseModelLoader() = default;
        virtual std::shared_ptr<Model> loadModel(std::string model_name, std::string file_name) = 0;

    protected:
        std::shared_ptr<BaseFileLoader> loader;
};

class BaseFileLoader
{
    public:
        BaseFileLoader() = default;
        ~BaseFileLoader() noexcept = default;

        virtual void open(std::string file_name) = 0;
        virtual bool isOpen() const = 0;
        virtual void close() = 0;
        virtual Vector<Point> readPoints() = 0;
        virtual Vector<Point> readConnections() = 0;
    
    private:
        std::ifstream file;
};

class ModelLoader : public BaseModelLoader
{
    public:
        ModelLoader(std::shared_ptr<BaseFileLoader> loader, std::shared_ptr<BaseModelBuilder> builder);
        std::shared_ptr<Model> loadModel(std::string model_name, std::string file_name) override;

    private:
        std::shared_ptr<BaseModelBuilder> builder;
};
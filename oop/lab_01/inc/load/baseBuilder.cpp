#include "baseBuilder.hpp"

bool BaseBuilder::buildCamera(std::ifstream& file)
{
    return true;
}

bool BaseBuilder::buildModel(std::ifstream& file)
{
    return true;
}

std::shared_ptr<Object> BaseBuilder::getObject()
{
    return object;
}


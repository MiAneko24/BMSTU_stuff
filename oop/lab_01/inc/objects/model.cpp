#include "model.hpp"
#include "../draw/visitor.h"

Model::Model(const Model &model) : frame(model.frame) {};

Model::Model(Model &&model) noexcept : frame(model.frame) {};

bool Model::isVisible() const
{
    return true;
}

Model& Model::operator =(const Model& model) noexcept
{
    if (this != &model)
    {
        frame = model.frame;
    }
    return *this;
}

void Model::transform(const Matrix<double> &transform_matrix)
{
    frame->transform(transform_matrix);    
}

void Model::accept(std::shared_ptr<Visitor> visitor)
{
    visitor->visit(*this);
}
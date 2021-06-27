#include "model.hpp"
#include "../draw/visitor.h"

Model::Model()
{
    frame = std::shared_ptr<FrameModel>(new FrameModel());
}

Model::Model(const Model &model) : frame(model.frame) {};

Model::Model(Model &&model) noexcept : frame(model.frame) {};

bool Model::isVisible() const
{
    return true;
}

Model& Model::operator =(const Model& model)
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

void Model::accept(Visitor &visitor)
{
    visitor.visit(*this);
}

std::shared_ptr<FrameModel> Model::getFrame()
{
    return frame;
}

Model::~Model()
{
    frame.reset();
}
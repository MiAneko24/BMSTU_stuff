#include "model.hpp"
#include "../draw/visitor.h"

#include "../draw/ObjectsVisitor.h"

Model::Model()
{
    frame = std::shared_ptr<FrameModel>(new FrameModel());
    type = ObjectType::MODEL;
}

Model::Model(std::shared_ptr<FrameModel> model) : frame(model)
{
    type = ObjectType::MODEL;
}

Model::Model(const Model &model) : frame(model.frame) {};

Model::Model(Model &&model) noexcept : frame(model.frame) {};

ObjectType Model::getType() const
{
    return type;
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

Model::~Model()
{
    frame.reset();
}
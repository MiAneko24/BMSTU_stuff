#ifndef MODEL_HPP
#define MODEL_HPP

#include "../base_elems/vector.hpp"
#include "../base_elems/matrix.hpp"
#include "object.hpp"
#include "frameModel.h"

class ObjectsVisitor;

class Model : public Object
{
    public:
        friend ObjectsVisitor;
        Model();
        Model(const Model &);
        Model(std::shared_ptr<FrameModel> model);
        Model(Model &&) noexcept;

        ObjectType getType() const override;

        Model& operator =(const Model&);
        Model& operator =(Model &&) noexcept;
        void transform(const Matrix<double> &transform_matrix) override;
        void accept(Visitor &visitor) override;

        ~Model();

    private:
        std::shared_ptr<FrameModel> frame;
};

#endif
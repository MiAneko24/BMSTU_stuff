#ifndef MODEL_HPP
#define MODEL_HPP

#include "../base_elems/vector.hpp"
#include "../base_elems/matrix.hpp"
#include "object.hpp"
#include "frameModel.h"

class Model : public Object
{
    public:
        Model();
        Model(const Model &);
        Model(Model &&) noexcept;

        bool isVisible() const override;

        Model& operator =(const Model&);
        Model& operator =(Model &&) noexcept;
        std::shared_ptr<FrameModel> getFrame();
        void transform(const Matrix<double> &transform_matrix) override;
        void accept(Visitor &visitor) override;

        ~Model();

    private:
        std::shared_ptr<FrameModel> frame;
};

#endif
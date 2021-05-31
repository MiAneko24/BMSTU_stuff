#ifndef MODEL_HPP
#define MODEL_HPP

#include "vector.hpp"
#include "matrix.hpp"
#include "object.hpp"
#include "frameModel.h"

class Model : public Object
{
    public:
        Model() = default;
        Model(const Model &);
        Model(Model &&) noexcept;
        ~Model() = default;

        bool isVisible() const override;

        Model& operator =(const Model&);
        Model& operator =(Model &&) noexcept;
        std::shared_ptr<FrameModel> getFrame();
        void transform(const Matrix<double> &transform_matrix) override;
        void accept(std::shared_ptr<Visitor> visitor) override;

    private:
        std::shared_ptr<FrameModel> frame;
};

#endif
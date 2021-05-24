#ifndef COMPOSITEOBJECT_HPP
#define COMPOSITEOBJECT_HPP
#include "object.hpp"

class CompositeObject : public Object 
{
    public:
        CompositeObject() = default;

        bool isVisible() const override;
        bool add(std::shared_ptr<Object> obj) override;
        bool remove(VectorIterator<std::shared_ptr<Object>> &it) override;
        bool isComposite() const override;

        virtual VectorIterator<std::shared_ptr<Object>> begin() override;
        virtual VectorIterator<std::shared_ptr<Object>> end() override;
        void transform(const Matrix<double> &transform_matrix) override;
        // void apply(std::shared_ptr<Visitor> visitor);
    private:
        Vector<std::shared_ptr<Object>> objects;
};

#endif
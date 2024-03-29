#ifndef COMPOSITEOBJECT_HPP
#define COMPOSITEOBJECT_HPP
#include "object.hpp"

class CompositeObject : public Object 
{
    public:
        CompositeObject();

        ObjectType getType() const override;
        bool add(std::shared_ptr<Object> obj) override;
        bool remove(VectorIterator<std::shared_ptr<Object>> &it) override;

        virtual VectorIterator<std::shared_ptr<Object>> begin() override;
        virtual VectorIterator<std::shared_ptr<Object>> end() override;
        void transform(const Matrix<double> &transform_matrix) override;
        void accept(Visitor &visitor) override;

        ~CompositeObject();

    private:
        Vector<std::shared_ptr<Object>> objects;
};

#endif
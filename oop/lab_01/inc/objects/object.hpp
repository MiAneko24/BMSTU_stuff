#include <iostream>
#include <memory>
#include "../matrix.hpp"
#include "../vectorIterator.hpp"

class Object
{
    public:
        Object() = default;
        ~Object() = default;

        virtual bool isVisible() const = 0;
        virtual bool isComposite() const 
        {
            return false;
        }
        virtual bool add(std::shared_ptr<Object> obj)
        {
            return false;
        }
        virtual bool remove(VectorIterator<std::shared_ptr<Object>> it)
        {
            return false;
        }

        virtual void transform(const Matrix<double> &transform_mat) = 0;

        virtual VectorIterator<std::shared_ptr<Object>> begin() 
        {
            return VectorIterator<std::shared_ptr<Object>>();
        }

        virtual VectorIterator<std::shared_ptr<Object>> end()
        {
            return VectorIterator<std::shared_ptr<Object>>();
        }
};


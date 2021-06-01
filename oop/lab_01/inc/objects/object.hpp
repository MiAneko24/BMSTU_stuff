#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <memory>
#include "../matrix.hpp"
#include "../vectorIterator.hpp"

class Visitor;

class Object
{
    public:
        Object() = default;
        ~Object() = default;

        virtual bool isVisible() const;
        virtual bool isComposite() const 
        {
            return false;
        }
        virtual bool add(std::shared_ptr<Object> obj)
        {
            return false;
        }
        virtual bool remove(VectorIterator<std::shared_ptr<Object>> &it)
        {
            return false;
        }

        virtual void transform(const Matrix<double> &transform_mat);

        virtual void accept(std::shared_ptr<Visitor> visitor);

        virtual VectorIterator<std::shared_ptr<Object>> begin() 
        {
            return VectorIterator<std::shared_ptr<Object>>();
        }

        virtual VectorIterator<std::shared_ptr<Object>> end()
        {
            return VectorIterator<std::shared_ptr<Object>>();
        }
};


#endif
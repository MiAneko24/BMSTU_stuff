#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <memory>
#include "../base_elems/matrix.hpp"
#include "../base_elems/vectorIterator.hpp"
#include "objectType.hpp"

class Visitor;

class Object
{
    public:
        virtual ObjectType getType() const = 0;
        virtual bool add(std::shared_ptr<Object> obj)
        {
            return false;
        }
        virtual bool remove(VectorIterator<std::shared_ptr<Object>> &it)
        {
            return false;
        }

        virtual void transform(const Matrix<double> &transform_mat) = 0;

        virtual void accept(Visitor &visitor) = 0;

        virtual VectorIterator<std::shared_ptr<Object>> begin() 
        {
            return VectorIterator<std::shared_ptr<Object>>();
        }

        virtual VectorIterator<std::shared_ptr<Object>> end()
        {
            return VectorIterator<std::shared_ptr<Object>>();
        }

        virtual ~Object() = default;

    protected:
        ObjectType type;
};


#endif
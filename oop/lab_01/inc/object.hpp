#include <iostream>
#include <memory>
#include "matrix.hpp"
class Object
{
    public:
        Object() = default;
        Object(std::string name) : oName(name){};
        ~Object() = default;

        virtual bool isVisible() const = 0;
        virtual bool isScene() const 
        {
            return false;
        }
        virtual bool add(std::shared_ptr<Object> obj)
        {
            return false;
        }
        virtual bool remove(IteratorObject &it)
        {
            return false;
        }

        virtual void transform(std::shared_ptr<Matrix<double>> mat) = 0;
        virtual std::string getName()
        {
            return oName; 
        }

    protected:
        std::string oName;
};


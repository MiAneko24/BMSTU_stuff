#ifndef OBJECTMANAGER_HPP
#define OBJECTMANAGER_HPP

#include "baseManager.hpp"
#include <memory>
#include "../objects/object.hpp"

class ObjectManager : public BaseManager
{
    public:
        void move(std::shared_ptr<Object> obj, Vector<double> &params);
        void scale(std::shared_ptr<Object> obj, Vector<double> &params);
        void rotate(std::shared_ptr<Object> obj, Vector<double> &params);
};

#endif
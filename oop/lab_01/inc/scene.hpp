#ifndef SCENE_CPP
#define SCENE_CPP

#include "object.hpp"

class Scene : public Object
{
    public:
        Scene() = default;

        bool isVisible() const override;
        bool add(std::shared_ptr<Object> obj) override;
        bool remove(IteratorObject &it) override;
        bool isScene() const override;
        void transform(const std::shared_ptr<Matrix<double>> mat);

    private:
        Vector<Object> scene_objects;
};

#endif
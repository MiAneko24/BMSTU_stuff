#include "objectManager.hpp"
#include "../matrix.hpp"
void ObjectManager::move(std::shared_ptr<Object> obj, Vector<double> &params)
{
    Matrix<double> transform_mat = Matrix<double>(4, 4);
    transform_mat.make_move_matrix(params);
    obj->transform(transform_mat);
}

void ObjectManager::scale(std::shared_ptr<Object> obj, Vector<double> &params)
{
    Matrix<double> transform_mat = Matrix<double>(4, 4);
    transform_mat.make_scale_matrix(params);
    obj->transform(transform_mat);
}

void ObjectManager::rotate(std::shared_ptr<Object> obj, Vector<double> &params)
{
    Matrix<double> transform_mat = Matrix<double>(4, 4);
    transform_mat.make_rotate_matrix(params);
    obj->transform(transform_mat);
}


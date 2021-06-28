#include "transformManager.h"

TransformManager::TransformManager(std::shared_ptr<SceneManager> manager)
{
    sceneManager = manager;
}

void TransformManager::move(ObjectType type_obj, Vector<double> &params)
{
    int pos = sceneManager->getCurrentObjectPos(type_obj);
    int curScene = sceneManager->getCurrentObjectPos(ObjectType::COMPOSITE);
    std::shared_ptr<Object> obj = sceneManager->getScene()->getObject(type_obj, pos, curScene);
    Matrix<double> transform_mat = Matrix<double>(4, 4);
    transform_mat.make_move_matrix(params);
    obj->transform(transform_mat);
}

void TransformManager::scale(ObjectType type_obj, Vector<double> &params)
{
    int pos = sceneManager->getCurrentObjectPos(type_obj);
    int curScene = sceneManager->getCurrentObjectPos(ObjectType::COMPOSITE);
    std::shared_ptr<Object> obj = sceneManager->getScene()->getObject(type_obj, pos, curScene);
    Matrix<double> transform_mat = Matrix<double>(4, 4);
    transform_mat.make_scale_matrix(params);
    obj->transform(transform_mat);
}

void TransformManager::rotate(ObjectType type_obj, Vector<double> &params)
{
    int pos = sceneManager->getCurrentObjectPos(type_obj);
    int curScene = sceneManager->getCurrentObjectPos(ObjectType::COMPOSITE);
    std::shared_ptr<Object> obj = sceneManager->getScene()->getObject(type_obj, pos, curScene);
    if (type_obj == ObjectType::MODEL)
    {
        Matrix<double> transform_mat = Matrix<double>(4, 4);
        transform_mat.make_rotate_matrix(params);
        obj->transform(transform_mat);
    }
    else if (type_obj == ObjectType::CAMERA)
    {
        Matrix<double> transform_mat = Matrix<double>(1, 3);
        transform_mat[0] = params;
        obj->transform(transform_mat);
    }
}

TransformManager::~TransformManager()
{
    sceneManager.reset();
}
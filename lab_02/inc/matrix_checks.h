#ifndef MATRIX_CHECKS_H
#define MATRIX_CHECKS_H

#include "matrix_templates.h"



template <typename T>
void Matrix<T>::checkNull()
{
    if (mRows == 0 || mColumns == 0)
    {
        time_t time_cur = time(nullptr);
        throw NullPointerError(ctime(&time_cur), __FILE__, typeid(*this).name(), __LINE__, "Attempt of creating matrix with null size");
    }
}

template <typename T>
void Matrix<T>::checkMulSizes(Matrix<T> &mat)
{
    if (mColumns != mat.getRows())
    {
        time_t time_cur = time(nullptr);
        throw DimensionMatrixError(ctime(&time_cur), __FILE__, typeid(*this).name(), __LINE__, "First matrix's amount of columns must be equal to second matrix's amount of rows");
    }
}

template <typename T>
void Matrix<T>::checkAddSizes(Matrix<T> &mat)
{
    if (mRows != mat.getRows() || mColumns != mat.getColumns())
    {

        time_t time_cur = time(nullptr);
        throw DimensionMatrixError(ctime(&time_cur), __FILE__, typeid(*this).name(), __LINE__, "For summary matrixes' dimensions must be equal");
    }
}

template <typename T>
void Matrix<T>::checkSquare()
{
    if (mRows != mColumns)
    {
        time_t time_cur = time(nullptr);
        throw DimensionMatrixError(ctime(&time_cur), __FILE__, typeid(*this).name(), __LINE__, "It is impossible to find determinant and reversed matrix for not square matrix");
    }
}

template <typename T>
void Matrix<T>::checkDeterminant()
{
    if (abs(det()) < 1e-8)
    { 
        time_t time_cur = time(nullptr);
        throw TypeMatrixError(ctime(&time_cur), __FILE__, typeid(*this).name(), __LINE__, "It is impossible to reverse matrix with null determinant");
    }
}

template <typename T>
void Matrix<T>::checkRowIndex(int i)
{
    if (i < 0 || i >= mRows)
    {
        time_t time_cur = time(nullptr);
        throw IndexError(ctime(&time_cur), __FILE__, typeid(*this).name(), __LINE__, "Index of rows is out of range");
    }
}

template <typename T>
void Matrix<T>::checkColumnIndex(int j)
{
    if (j < 0 || j > mColumns)
    {
        time_t time_cur = time(nullptr);
        throw IndexError(ctime(&time_cur), __FILE__, typeid(*this).name(), __LINE__, "Index of columns is out of range");
    }
}

template <typename T>
void Matrix<T>::check_reversing_matrix()
{
    checkOperationsType();
    checkSquare();
    checkDeterminant();
}

template <typename T>
void Matrix<T>::checkMatrixSource(T **source)
{
    if (source == nullptr)
    {
        time_t time_cur = time(nullptr);
        throw NullPointerError(ctime(&time_cur), __FILE__, typeid(*this).name(), __LINE__, "Attempt of creating matrix from nullptr");
    }
}

template <typename T>
void Matrix<T>::checkDivider(T &elem)
{
    if (abs(elem) < 1e-8)
    {
        time_t time_cur = time(nullptr);
        throw DivisionByZeroError(ctime(&time_cur), __FILE__, typeid(*this).name(), __LINE__, "Error division by zero");
    }
}

template <typename T>
void Matrix<T>::checkOperationsType()
{
    if (typeid(T).name() != typeid(int).name() && typeid(T).name() != typeid(float).name() && typeid(T).name() != typeid(double).name())
    {
        time_t time_cur = time(nullptr);
        throw TypeMatrixError(ctime(&time_cur), __FILE__, typeid(*this).name(), __LINE__, "Math operations exist only for numeric matrixes");
    }
}

template <typename T>
void Matrix<T>::checkList(std::initializer_list<std::initializer_list<T>> list)
{
    if (list.size() == 0)
    {
        time_t time_cur = time(nullptr);
        throw NullPointerError(ctime(&time_cur), __FILE__, typeid(*this).name(), __LINE__, "It is impossible to create a matrix from void list");
    }
}

#endif
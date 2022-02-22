#ifndef MATRIX_CHECKS_HPP
#define MATRIX_CHECKS_HPP

#include "matrix.hpp"



template <typename T>
void Matrix<T>::checkNull(std::string file, int line) const
{
    if (mRows == 0 || mColumns == 0)
    {
        time_t time_cur = time(nullptr);
        throw NullPointerError(ctime(&time_cur), file, typeid(*this).name(), line, "Attempt of creating matrix with null size");
    }
}

template <typename T>
void Matrix<T>::checkMulSizes(const Matrix<T> &mat, std::string file, int line) const
{
    if (mColumns != mat.getRows())
    {
        time_t time_cur = time(nullptr);
        throw DimensionMatrixError(ctime(&time_cur), file, typeid(*this).name(), line, "First matrix's amount of columns must be equal to second matrix's amount of rows");
    }
}

template <typename T>
void Matrix<T>::checkAddSizes(const Matrix<T> &mat, std::string file, int line) const
{
    if (mRows != mat.getRows() || mColumns != mat.getColumns())
    {

        time_t time_cur = time(nullptr);
        throw DimensionMatrixError(ctime(&time_cur), file, typeid(*this).name(), line, "For summary matrixes' dimensions must be equal");
    }
}

template <typename T>
void Matrix<T>::checkSquare(std::string file, int line) const
{
    if (mRows != mColumns)
    {
        time_t time_cur = time(nullptr);
        throw DimensionMatrixError(ctime(&time_cur), file, typeid(*this).name(), line, "It is impossible to find determinant and reversed matrix for not square matrix");
    }
}


template <typename T>
void Matrix<T>::checkRowIndex(int i, std::string file, int line) const
{
    if (i < 0 || i >= mRows)
    {
        time_t time_cur = time(nullptr);
        throw IndexError(ctime(&time_cur), file, typeid(*this).name(), line, "Index of rows is out of range");
    }
}


template <typename T>
void Matrix<T>::checkMatrixSource(T **source, std::string file, int line) const
{
    if (source == nullptr)
    {
        time_t time_cur = time(nullptr);
        throw NullPointerError(ctime(&time_cur), file, typeid(*this).name(), line, "Attempt of creating matrix from nullptr");
    }
}

template <typename T>
void Matrix<T>::checkDivider(T &elem, std::string file, int line) const
{
    if (abs(elem) < 1e-8)
    {
        time_t time_cur = time(nullptr);
        throw DivisionByZeroError(ctime(&time_cur), file, typeid(*this).name(), line, "Error division by zero");
    }
}

template <typename T>
void Matrix<T>::checkOperationsType(std::string file, int line) const
{
    if (typeid(T).name() != typeid(int).name() && typeid(T).name() != typeid(float).name() && typeid(T).name() != typeid(double).name())
    {
        time_t time_cur = time(nullptr);
        throw TypeMatrixError(ctime(&time_cur), file, typeid(*this).name(), line, "Math operations exist only for numeric matrixes");
    }
}

template <typename T>
void Matrix<T>::checkList(std::initializer_list<std::initializer_list<T>> list, std::string file, int line) const
{
    if (list.size() == 0)
    {
        time_t time_cur = time(nullptr);
        throw NullPointerError(ctime(&time_cur), file, typeid(*this).name(), line, "It is impossible to create a matrix from void list");
    }
}

#endif
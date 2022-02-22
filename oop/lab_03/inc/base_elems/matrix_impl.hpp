#ifndef MATRIX_IMPL_HPP
#define MATRIX_IMPL_HPP
#include "matrix.hpp"
#include "vector.hpp"
#include <math.h>

template <typename T>
Matrix<T>& Matrix<T>::operator =(const Matrix<T> &matrix)
{
    copy(matrix);
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator =(Matrix<T> &&matrix)
{
    allocateMatrix(matrix.getRows(), matrix.getColumns());
    for (int i = 0; i < mRows; i++)
        for (int j = 0; j < mColumns; j++)
            this->operator[](i)[j] = matrix[i][j];
    matrix.reset();
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator =(std::initializer_list<std::initializer_list<T>> list)
{
    checkList(list, __FILE__, __LINE__);
    size_t rows = list.size();
    auto it = list.begin();
    size_t columns = it->size();
    
    allocateDataArray(rows, columns);
    size_t i = 0;
    for (const auto &row : list)
    {
        this->operator[](i) = Matrix<T>::MatrixRow(row);
        i++;
    }
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::add(const Matrix<T> &mat) const
{
    checkOperationsType(__FILE__, __LINE__);
    checkAddSizes(mat, __FILE__, __LINE__);
    Matrix<T> res = Matrix<T>(mRows, mColumns);
    for (int i = 0; i < mRows; i++)
        for (int j = 0; j < mColumns; j++)
            res[i][j] = this->operator[](i)[j] + mat[i][j];
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator +(const Matrix<T> &mat) const
{
    Matrix<T> res = add(mat);
    return res;
}

template <typename T>
void Matrix<T>::addEq(const Matrix<T>& mat)
{
    checkOperationsType(__FILE__, __LINE__);
    checkAddSizes(mat, __FILE__, __LINE__);
    for (int i = 0; i < mRows; i++)
        for (int j = 0; j < mColumns; j++)
            this->operator[](i)[j] += mat[i][j];
}

template <typename T>
Matrix<T>& Matrix<T>::operator +=(const Matrix<T> &mat)
{
    addEq(mat);
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::sub(const Matrix<T> &mat) const
{
    checkOperationsType(__FILE__, __LINE__);
    checkAddSizes(mat, __FILE__, __LINE__);
    Matrix<T> res = Matrix<T>(mRows, mColumns);
    for (int i = 0; i < mRows; i++)
        for (int j = 0; j < mColumns; j++)
            res[i][j] = this->operator[](i)[j] - mat[i][j];
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator -(const Matrix<T> &mat) const
{
    Matrix<T> res = sub(mat);
    return res;
}

template <typename T>
void Matrix<T>::subEq(const Matrix<T> &mat)
{
    checkOperationsType(__FILE__, __LINE__);
    checkAddSizes(mat, __FILE__, __LINE__);
    for (int i = 0; i < mRows; i++)
        for (int j = 0; j < mColumns; j++)
            this->operator[](i)[j] -= mat[i][j];
}

template <typename T>
Matrix<T>& Matrix<T>::operator -=(const Matrix<T> &mat)
{
    subEq(mat);
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::mul(const Matrix<T> &mat) const
{
    checkOperationsType(__FILE__, __LINE__);
    checkMulSizes(mat, __FILE__, __LINE__);

    Matrix<T> res = Matrix<T>(mRows, mat.getColumns());
    for (int i = 0; i < res.getRows(); i++)
        for (int j = 0; j < res.getColumns(); j++)
            for (int k = 0; k < mColumns; k++)
                res[i][j] += this->operator[](i)[k] * mat[k][j];
    return res;
}
       
template <typename T>
Matrix<T> Matrix<T>::operator *(const Matrix<T> &mat) const
{
    Matrix<T> res = mul(mat);
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::mul(const T &elem) const
{
    checkOperationsType(__FILE__, __LINE__);
    Matrix<T> res = Matrix<T>(mRows, mColumns);
    for (int i = 0; i < mRows; i++)
        for (int j = 0; j < mColumns; j++)
            res[i][j] = this->operator[](i)[j] * elem;
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator *(const T &elem) const
{
    Matrix<T> res = mul(elem);
    return res;
}

template <typename T>
void Matrix<T>::mulEq(const T &elem)
{
    checkOperationsType(__FILE__, __LINE__);

    for (int i = 0; i < mRows; i++)
        for (int j = 0; j < mColumns; j++)
            this->operator[](i)[j] *= elem;
}

template <typename T>
Matrix<T>& Matrix<T>::operator *=(const T& elem)
{
    mulEq(elem);
    return *this;
}

template <typename T>
bool Matrix<T>::operator ==(const Matrix<T> &mat) const noexcept
{
    bool result = true;
    if (mRows != mat.getRows() || mColumns != mat.getColumns())
        result = false;
    for (int i = 0; i < mRows && result; i++)
    {
        if (this->operator[](i) != mat[i])
            result = false;
    }
    return result;
}

template <typename T>
bool Matrix<T>::operator !=(const Matrix<T> &mat) const noexcept
{
    bool result = false;
    if (mRows != mat.getRows() || mColumns != mat.getColumns())
        result = true;
    for (int i = 0; i < mRows && !result; i++)
        if (this->operator[](i) == mat[i])
            result = true;
    return result;
}


template <typename T>
void Matrix<T>::make_e_matrix()
{
    for (int i = 0; i < mRows; i++)
        for (int j = 0; j < mColumns; j++)
            this->operator[](i)[j] = int(i == j);
}

template <typename T>
void Matrix<T>::make_move_matrix(Vector<T> &params)
{
    for (int i = 0; i < mRows; i++)
        (*this)[i][i] = 1;
    
    for (int i = 0; i < mRows - 1; i++)
        (*this)[mRows - 1][i] = params[i];
}

template <typename T>
void Matrix<T>::make_scale_matrix(Vector<T> &params)
{
    for (int i = 0; i < mRows - 1; i++)
        (*this)[i][i] = params[i];
    
    (*this)[3][3] = 1;   
}

template <typename T>
void Matrix<T>::make_rotate_matrix(Vector<T> &params)
{
    Matrix<T> x_rotation = make_rotate_ox_matrix(params[0]);
    Matrix<T> y_rotation = make_rotate_oy_matrix(params[1]);
    Matrix<T> z_rotation = make_rotate_oz_matrix(params[2]);

    Matrix<T> res = x_rotation * y_rotation;
    (*this) = res * z_rotation;
}

template <typename T>
Matrix<T> Matrix<T>::make_rotate_ox_matrix(T obj)
{
    Matrix<T> mat = Matrix<T>(4, 4);
    mat[1][1] = cos(obj);
    mat[1][2] = -sin(obj);
    mat[2][1] = sin(obj);
    mat[2][2] = cos(obj);
    mat[0][0] = 1;
    mat[3][3] = 1;
    return mat;
}

template <typename T>
Matrix<T> Matrix<T>::make_rotate_oy_matrix(T obj)
{
    Matrix<T> mat = Matrix<T>(4, 4);
    mat[0][0] = cos(obj);
    mat[0][2] = sin(obj);
    mat[2][0] = -sin(obj);
    mat[2][2] = cos(obj);
    mat[1][1] = 1;
    mat[3][3] = 1;
    return mat;
}

template <typename T>
Matrix<T> Matrix<T>::make_rotate_oz_matrix(T obj)
{
    Matrix<T> mat = Matrix<T>(4, 4);
    mat[0][0] = cos(obj);
    mat[0][1] = -sin(obj);
    mat[1][0] = sin(obj);
    mat[1][1] = cos(obj);
    mat[2][2] = 1;
    mat[3][3] = 1;
    return mat;
}

template <typename T>
void Matrix<T>::make_project_matrix()
{
    (*this)[0][0] = 1;
    (*this)[1][1] = 1;
    (*this)[2][2] = 10/9;
    (*this)[2][3] = 1;
    (*this)[3][2] = -10/9;
}

#endif
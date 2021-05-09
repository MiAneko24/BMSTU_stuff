#ifndef MATRIX_IMPL_HPP
#define MATRIX_IMPL_HPP
#include "matrix.hpp"

template <typename T>
Matrix<T>& Matrix<T>::operator =(Matrix<T> &matrix)
{
    copy(matrix);
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator =(Matrix<T> &&matrix)
{
    move(matrix);
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator =(const Matrix<T> &matrix)
{
    copy(matrix);
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator =(const Matrix<T> &&matrix)
{
    move(matrix);
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
Matrix<T> Matrix<T>::add(Matrix<T> &mat)
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
Matrix<T> Matrix<T>::operator +(Matrix<T> &mat)
{
    Matrix<T> res = add(mat);
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::add(const Matrix<T> &mat)
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
Matrix<T> Matrix<T>::operator +(const Matrix<T> &mat)
{
    Matrix<T> res = add(mat);
    return res;
}

template <typename T>
void Matrix<T>::addEq(Matrix<T>& mat)
{
    checkOperationsType(__FILE__, __LINE__);
    checkAddSizes(mat, __FILE__, __LINE__);
    for (int i = 0; i < mRows; i++)
        for (int j = 0; j < mColumns; j++)
            this->operator[](i)[j] += mat[i][j];
}

template <typename T>
Matrix<T>& Matrix<T>::operator +=(Matrix<T> &mat)
{
    addEq(mat);
    return *this;
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
Matrix<T> Matrix<T>::sub(Matrix<T> &mat)
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
Matrix<T> Matrix<T>::operator -(Matrix<T> &mat)
{
    Matrix<T> res = sub(mat);
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::sub(const Matrix<T> &mat)
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
Matrix<T> Matrix<T>::operator -(const Matrix<T> &mat)
{
    Matrix<T> res = sub(mat);
    return res;
}

template <typename T>
void Matrix<T>::subEq(Matrix<T> &mat)
{
    checkOperationsType(__FILE__, __LINE__);
    checkAddSizes(mat, __FILE__, __LINE__);
    for (int i = 0; i < mRows; i++)
        for (int j = 0; j < mColumns; j++)
            this->operator[](i)[j] -= mat[i][j];
}

template <typename T>
Matrix<T>& Matrix<T>::operator -=(Matrix<T> &mat)
{
    subEq(mat);
    return *this;
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
Matrix<T> Matrix<T>::mul(Matrix<T> &mat)
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
Matrix<T> Matrix<T>::operator *(Matrix<T> &mat)
{
    Matrix<T> res = mul(mat);
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::mul(const Matrix<T> &mat)
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
Matrix<T> Matrix<T>::operator *(const Matrix<T> &mat)
{
    Matrix<T> res = mul(mat);
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::mul(T &elem)
{
    checkOperationsType(__FILE__, __LINE__);
    Matrix<T> res = Matrix<T>(mRows, mColumns);
    for (int i = 0; i < mRows; i++)
        for (int j = 0; j < mColumns; j++)
            res[i][j] = this->operator[](i)[j] * elem;
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator *(T &elem)
{
    Matrix<T> res = mul(elem);
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::mul(const T &elem)
{
    checkOperationsType(__FILE__, __LINE__);
    Matrix<T> res = Matrix<T>(mRows, mColumns);
    for (int i = 0; i < mRows; i++)
        for (int j = 0; j < mColumns; j++)
            res[i][j] = this->operator[](i)[j] * elem;
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator *(const T &elem)
{
    Matrix<T> res = mul(elem);
    return res;
}

template <typename T>
void Matrix<T>::mulEq(T &elem)
{
    checkOperationsType(__FILE__, __LINE__);

    for (int i = 0; i < mRows; i++)
        for (int j = 0; j < mColumns; j++)
            this->operator[](i)[j] *= elem;
}

template <typename T>
Matrix<T>& Matrix<T>::operator *=(T& elem)
{
    mulEq(elem);
    return *this;
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
Matrix<T> Matrix<T>::div(T &elem)
{
    checkOperationsType(__FILE__, __LINE__);
    checkDivider(elem, __FILE__, __LINE__);
    Matrix<T> res = Matrix<T>(mRows, mColumns);
    for (int i = 0; i < mRows; i++)
        for (int j = 0; j < mColumns; j++)
            res[i][j] = this->operator[](i)[j] / elem;
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator /(T &elem)
{
    Matrix<T> res = div(elem);
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::div(const T &elem)
{
    checkOperationsType(__FILE__, __LINE__);
    checkDivider(elem, __FILE__, __LINE__);
    Matrix<T> res = Matrix<T>(mRows, mColumns);
    for (int i = 0; i < mRows; i++)
        for (int j = 0; j < mColumns; j++)
            res[i][j] = this->operator[](i)[j] / elem;
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator /(const T &elem)
{
    Matrix<T> res = div(elem);
    return res;
}

template <typename T>
void Matrix<T>::divEq(T &elem)
{
    checkOperationsType(__FILE__, __LINE__);
    checkDivider(elem, __FILE__, __LINE__);
    for (int i = 0; i < mRows; i++)
        for (int j = 0; j < mColumns; j++)
            this->operator[](i)[j] /= elem;
}

template <typename T>
Matrix<T>& Matrix<T>::operator /=(T& elem)
{
    divEq(elem);
    return *this;
}

template <typename T>
void Matrix<T>::divEq(const T &elem)
{
    checkOperationsType(__FILE__, __LINE__);
    checkDivider(elem, __FILE__, __LINE__);
    for (int i = 0; i < mRows; i++)
        for (int j = 0; j < mColumns; j++)
            this->operator[](i)[j] /= elem;
}

template <typename T>
Matrix<T>& Matrix<T>::operator /=(const T& elem)
{
    divEq(elem);
    return *this;
}

template <typename T>
bool Matrix<T>::operator ==(Matrix<T> &mat) const noexcept
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
bool Matrix<T>::operator !=(Matrix<T> &mat) const noexcept
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


#endif
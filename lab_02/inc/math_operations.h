#ifndef MATH_OPERATIONS_H
#define MATH_OPERATIONS_H

#include "matrix_templates.h"

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
bool Matrix<T>::operator ==(Matrix<T> &mat) noexcept
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
bool Matrix<T>::operator !=(Matrix<T> &mat) noexcept
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
bool Matrix<T>::operator ==(const Matrix<T> &mat) noexcept
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
bool Matrix<T>::operator !=(const Matrix<T> &mat) noexcept
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
T Matrix<T>::det()
{
    checkOperationsType(__FILE__, __LINE__);
    return determinant_recursive(*this);
}

template <typename T>
Matrix<T> Matrix<T>::transpose()
{
    Matrix<T> tmp = Matrix(mColumns, mRows);
    for (int i = 0; i < mRows; i++)
        for (int j = 0; j < mColumns; j++)
            tmp[j][i] = this->operator[](i)[j];
    return tmp;
}

template <typename T>
Matrix<T> Matrix<T>::reverse_matrix()
{
    checkOperationsType(__FILE__, __LINE__);
    check_reversing_matrix(__FILE__, __LINE__);

    Matrix<T> result = Matrix<T>(mRows, mColumns);
    result.make_e_matrix();
    int i = 0;
    while (i < mRows)
    {
        elementary_transf(result, i, 1);
    }
    i = mRows - 1;
    while (i >= 0)
    {
        elementary_transf(result, i, -1);
    }
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
T Matrix<T>::determinant_recursive(Matrix<T> &matrix)
{
    T det = 0;
    if (matrix.getRows() == 1)
        det += matrix[0][0];
    else
    {
        Matrix<T> tmp = Matrix<T>(matrix.getRows() - 1, matrix.getColumns() - 1);
        
        for (int i = 0; i < matrix.getRows(); i++)
        {
            matrix.fill_additional_matrix(tmp, matrix, i);
            det += matrix[0][i] * matrix.determinant_recursive(tmp) * sign(i);
        }
    }
    return det;    
}

template <typename T>
void Matrix<T>::swap_rows(int i, int j)
{
    Matrix<T>::MatrixRow tmp = Matrix<T>::MatrixRow(mColumns);
    this->operator[](i).copy(this->operator[](j));
    this->operator[](j).copy(tmp);
    tmp.reset();
}

template <typename T>
int Matrix<T>::sign(int i)
{
    return (i % 2 == 0) ? 1 : -1;
}

template <typename T>
void Matrix<T>::fill_additional_matrix(Matrix<T> &tmp, Matrix<T> &mat, size_t k) noexcept
{
    int cnt = 0;
    for (int i = 1; i < mat.getRows(); i++)
    {
        for (int j = 0; j < mat.getColumns(); j++)
        {
            if (j != k)
            {
                tmp[cnt / tmp.getColumns()][cnt % tmp.getColumns()] = mat[i][j];
                cnt++;
            }
        }
    }
}

template <typename T>
void Matrix<T>::elementary_transf(Matrix<T> &mat_res, int &i, int step)
{
    T divider = this->operator[](i)[i];
    if (divider != 0)
    {
        for (int j = (step > 0) ? 0 : mRows - 1; ((step > 0) && (j < mRows)) \
            || ((step < 0) && (j >= 0)); j += step)
        {
            this->operator[](i)[j] /= divider;
            mat_res[i][j] /= divider;
        }
        for (int j = i + step; ((step > 0) && (j < mRows)) \
            || ((step < 0) && (j >= 0)); j += step)
        {
            divider = this->operator[](j)[i] / this->operator[](i)[i];
            divider *= -1;
            for (int k = (step > 0) ? 0 : mRows - 1; ((step > 0) && (k < mColumns)) \
                || ((step < 0) && (k >= 0)); k += step)
            {
                this->operator[](j)[k] += divider * this->operator[](i)[k];
                mat_res[j][k] += divider * mat_res[i][k];
            }
        }
        i += step;
    }
    else
    {
        if (((i != mRows - 1) && (step > 0)) || ((i != 0) && (step < 0)))
        {
            int j;
            for (j = i + step; (((step > 0) && (j < mRows)) \
                || ((step < 0) && (j >= 0))) && (this->operator[](j)[i] == 0); j += step);
            if (this->operator[](j)[i] != 0)
            {
                swap_rows(j, i);
            }
            if (this->operator[](i)[i] == 0)
                i += step;
        }
        else
        {
            i += step;
        }
    }
}

#endif
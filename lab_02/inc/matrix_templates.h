#include <memory>
#include <iostream>
#include "base_matrix_class.h"
#include "matrix_row.h"

template <typename T>
class Matrix : public BaseMatrix {
    private:
        std::shared_ptr<MatrixRow *> data;
        void checkSumSizes(Matrix<T> &matrix);
        void checkSquare();
        void checkMulSizes(Matrix<T> &matrix);
        void checkIndex();
        void allocateMatrix(size_t rows, size_t columns); //DONE
        void fill_additional_matrix(Matrix<T> &tmp, size_t k);

        T determinant_recursive(Matrix<T> &matrix);
        void swap_rows(int i, int j);
        int sign(int i);
        void move(Matrix<T> &&matrix);
        void copy(Matrix<T> &matrix);

        void move(Matrix<T> &matrix);

        void elementary_transf(Matrix<T> &mat_res, int &i, int step);
        void check_reversing_matrix();
        Matrix<T> addEq(Matrix<T> &matrix);
        Matrix<T> subEq(Matrix<T> &matrix);
        Matrix<T> mulEq(T &elem);
        Matrix<T> divEq(T &elem);

        Matrix<T> add(Matrix<T> &mat_1, Matrix<T> &mat_2);
        Matrix<T> sub(Matrix<T> &mat_from, Matrix<T> &mat_sub);
        Matrix<T> mul(Matrix<T> &mat_first, Matrix<T> &mat_second);
        Matrix<T> mul(Matrix<T> &mat, T &elem);
        Matrix<T> div(Matrix<T> &mat, T &elem);
    public:

        void reset(MatrixRow<T> *new_data); //DONE
        void reset(); //DONE
        Matrix(std::initializer_list<std::initializer_list<T>> list); //DONE
        explicit Matrix(Matrix<T> &matrix); //DONE
        Matrix(size_t rows, size_t columns); //DONE
        Matrix(T &fill_with, size_t rows, size_t columns); //DONE
        Matrix(T **source, size_t rows, size_t columns); //DONE
        Matrix(Matrix<T> &&matrix);

        Matrix<T> operator *(Matrix<T> &mat); //DONE
        Matrix<T> operator *(T &elem); //DONE
        Matrix<T> operator *=(T &elem); 
        
        Matrix<T> operator +(Matrix<T> &mat); //DONE
        Matrix<T> operator +=(Matrix<T> &mat);

        Matrix<T> operator /(T &elem); //DONE
        Matrix<T> operator /=(T &elem);

        Matrix<T> operator -(Matrix<T> &mat); //DONE
        Matrix<T> operator -=(Matrix<T> &mat);
        MatrixRow<T>& operator [](size_t pos); //DONE

        Matrix<T>& operator =(std::initializer_list<std::initializer_list<T>> list);
        Matrix<T>& operator =(Matrix<T> &matrix);
        Matrix<T>& operator =(Matrix<T> &&matrix);
        T& operator ()(int i, int j);
        
        T det();
        void transpose();

        void make_e_matrix();

        void reverse_matrix();

};



template <typename T>
MatrixRow<T>& Matrix<T>::operator[](size_t pos)
{
    return data[pos];
}

template <typename T>
void Matrix<T>::move(Matrix<T> &&matrix)
{
    allocateMatrix(matrix.getRows, matrix.getColumns);
    for (int i = 0; i < mRows; i++)
        for (int j = 0; j < mColumns; j++)
            this[i][j] = matrix[i][j];
    matrix.reset();
}

template <typename T>
void Matrix<T>::move(Matrix<T> &matrix)
{
    allocateMatrix(matrix.getRows, matrix.getColumns);
    for (int i = 0; i < mRows; i++)
        for (int j = 0; j < mColumns; j++)
            this[i][j] = matrix[i][j];
    matrix.reset();
}

template <typename T>
void Matrix<T>::copy(Matrix<T> &matrix)
{
    allocateMatrix(matrix.getRows, matrix.getColumns);
    for (int i = 0; i < mRows; i++)
        for (int j = 0; j < mColumns; j++)
            this[i][j] = matrix[i][j];
}

template <typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> list)
{
    size_t rows = list.size();
    auto it = list.begin();
    size_t columns = it->size();
    //check
    allocateMatrix(rows, columns);
    size_t i = 0;
    for (const auto &row : list)
    {
        size_t j = 0;
        for (const auto &column : row)
        {
            this[i][j] = column;
            j++;
        }
        i++;
    }
}

template <typename T>
void Matrix<T>::allocateMatrix(size_t rows, size_t columns)
{
    mRows = rows;
    mColumns = columns;
    data.reset(new MatrixRow<T>[mRows]);
    for (int i = 0; i < mColumns; i++)
        data[i].allocateMatrixRow(mColumns);
}

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t columns)
{
    allocateMatrix(rows, columns);
}

template <typename T>
Matrix<T>::Matrix(T &fill_with, size_t rows, size_t columns)
{
    allocateMatrix(rows, columns);
    for (int i = 0; i < rows, i++)
        for (int j = 0; j < columns; j++)
            this[i][j] = fill_with;
}

template <typename T>
Matrix<T>::Matrix(T **source, size_t rows, size_t columns)
{
    //check
    allocateMatrix(rows, columns);
    for (int i = 0; i < mRows; i++)
        for (int j = 0; j < mColumns; j++)
            this[i][j] = source[i][j];
}

template <typename T>
Matrix<T>::Matrix(Matrix<T> &matrix)
{
    copy(matrix);
}

template <typename T>
void Matrix<T>::reset()
{
    for (int i = 0; i < mRows; i++)
        data[i].reset();
    data.reset();
}

template <typename T>
void Matrix<T>::reset(MatrixRow<T> *new_data)
{
    reset();
    data.reset(new_data);
}

template <typename T>
Matrix<T>::Matrix(Matrix<T> &&matrix)
{
    move(matrix);
}


template <typename T>
Matrix<T> mulEq(T &elem)
{
    for (int i = 0; i < mRows; i++)
        for (int j = 0; j < mColumns; j++)
            this[i][j] *= elem;
    return *this;
}

template <typename T>
Matrix<T> mul(Matrix<T> &mat_first, Matrix<T> &mat_second)
{
    Matrix<T> res = Matrix<T>(mat_first.mRows, mat_second.mColumns);
    for (int i = 0; i < res.mRows; i++)
        for (int j = 0; j < res.mColumns; j++)
            for (int k = 0; k < mat_first.mColumns; k++)
                res[i][j] += mat_first[i][k] * mat_second[k][j];
    return res;
}


template <typename T>
Matrix<T> mul(Matrix<T> &mat, T &elem)
{
    Matrix<T> res = Matrix<T>(mRows, mColumns);
    for (int i = 0; i < mRows; i++)
        for (int j = 0; j < mColumns; j++)
            res[i][j] = mat[i][j] * elem;
    return res;
}
       
template <typename T>
Matrix<T> Matrix<T>::operator *(Matrix<T> &mat)
{
    //check_sizes
    Matrix<T> res = Matrix<T>(mRows, mat.mColumns);
    for (int i = 0; i < mRows; i++)
        for (int j = 0; j < mat.mColumns; j++)
            for (int k = 0; k < mColumns; k++)
                res[i][j] += this[i][k] * mat[k][j];
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator *(T &elem)
{
    Matrix<T> res = Matrix<T>(mRows, mColumns);
    for (int i = 0; i < mRows; i++)
        for (int j = 0; j < mColumns; j++)
            res[i][j] = this[i][j] * elem;
    return res;
}


template <typename T>
Matrix<T> addEq(Matrix<T>& mat)
{
    //check
    for (int i = 0; i < mRows; i++)
        for (int j = 0; j < mColumns; j++)
            this[i][j] += mat[i][j];
    return *this;
}

template <typename T>
Matrix<T> add(Matrix<T> &mat)
{
    //check
    Matrix<T> res = Matrix<T>(mRows, mColumns);
    for (int i = 0; i < mRows; i++)
        for (int j = 0; j < mColumns; j++)
            res[i][j] = this[i][j] + mat[i][j];
    return res;
}


template <typename T>
Matrix<T> Matrix<T>::operator +(Matrix<T> &mat)
{
    //check_sizes
    Matrix<T> res = Matrix<T>(mRows, mColumns);
    for (int i = 0; i < mRows; i++)
        for (int j = 0; j < mColumns; j++)
            res[i][j] = this[i][j] + mat[i][j];
    return res;
}



template <typename T>
Matrix<T> Matrix<T>::divEq(T &elem)
{
    for (int i = 0; i < mRows; i++)
        for (int j = 0; j < mColumns; j++)
            res[i][j] /= elem;
    return *this;
}



template <typename T>
Matrix<T> Matrix<T>::div(Matrix<T> &mat, T &elem)
{
    Matrix<T> res = Matrix<T>(mRows, mColumns);
    for (int i = 0; i < mRows; i++)
        for (int j = 0; j < mColumns; j++)
            res[i][j] = mat[i][j] / elem;
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator /(T &elem)
{
    //check type && non_null?
    Matrix<T> res = Matrix<T>(mRows, mColumns);
    for (int i = 0; i < mRows; i++)
        for (int j = 0; j < mColumns; j++)
            res[i][j] = this[i][j] / elem;
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::subEq(Matrix<T> &matrix)
{
    for (int i = 0; i < mRows; i++)
        for (int j = 0; j < mColumns; j++)
            this[i][j] -= mat[i][j];
    return *this;
}

template <typename T>
Matrix<T> Matrix<T>::sub(Matrix<T> &mat_from, Matrix<T> &mat_sub)
{
    Matrix<T> res = Matrix<T>(mRows, mColumns);
    for (int i = 0; i < mRows; i++)
        for (int j = 0; j < mColumns; j++)
            res[i][j] = mat_from[i][j] - mat_sub[i][j];
    return res;
}

template <typename T>
Matrix<T> Matrix<T>::operator -(Matrix<T> &mat)
{
    //check_sizes
    Matrix<T> res = Matrix<T>(mRows, mColumns);
    for (int i = 0; i < mRows; i++)
        for (int j = 0; j < mColumns; j++)
            res[i][j] = this[i][j] - mat[i][j];
    return res;
}

template <typename T>
T Matrix<T>::det()
{
    //check
    return determinant_recursive(this);
}

template <typename T>
void Matrix<T>::fill_additional_matrix(Matrix<T> &tmp, size_t k)
{
    int cnt = 0;
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j != k)
            {
                tmp[0][cnt] = this[i][j];
                cnt++;
            }
        }
    }
}


template <typename T>
int Matrix<T>::sign(int i)
{
    return (i % 2 == 0) ? 1 : -1;
}

template <typename T>
T Matrix<T>::determinant_recursive(Matrix<T> &matrix)
{
    T det = 0;
    if (matrix.getRows() == 1)
        det += matrix[0][0];
    else
    {
        Matrix<T> tmp = new Matrix<T>(matrix.getRows() - 1, matrix.getRows() - 1);
        
        for (int i = 0; i < matrix.getRows(); i++)
        {
            matrix.fill_additional_matrix(tmp, i);
            det += matrix[0][i] * matrix.determinant_recursive(tmp) * sign(i);
        }
        tmp.reset();
    }
    return det;    
}




template <typename T>
void Matrix<T>::make_e_matrix()
{
    for (int i = 0; i < mRows; i++)
        this[i][i] = 1;
}

template <typename T>
void Matrix<T>::swap_rows(int i, int j)
{
    MatrixRow<T> tmp = new MatrixRow<T>(data[i]);
    data[i] = data[j];
    data[j] = tmp;
    tmp.reset();
}

template <typename T>
void Matrix<T>::elementary_transf(Matrix<T> &mat_res, int &i, int step)
{
    T divider = this[i][i];
    if (divider != 0)
    {
        for (int j = (step > 0) ? 0 : mRows - 1; ((step > 0) && (j < mRows)) \
            || ((step < 0) && (j >= 0)); j += step)
        {
            this[i][j] /= divider;
            mat_res[i][j] /= divider;
        }
        for (int j = i + step; ((step > 0) && (j < mRows)) \
            || ((step < 0) && (j >= 0)); j += step)
        {
            divider = this[j][i] / this[i][i];
            divider *= -1;
            for (int k = (step > 0) ? 0 : mRows - 1; ((step > 0) && (k < mColumns)) \
                || ((step < 0) && (k >= 0)); k += step)
            {
                this[j][k] += divider * this[i][k];
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
                || ((step < 0) && (j >= 0))) && (this[j][i] == 0); j += step);
            if (this[j][i] != 0)
            {
                swap_pointers(data[j], data[i]);
                swap_pointers(mat_res + j, mat_res + i);
            }
            if (mat_1[*i][*i] == 0)
                (*i) += step;
        }
        else
        {
            (*i) += step;
        }
    }
}


template <typename T>
void Matrix<T>::reverse_matrix()
{
    check_reversing_matrix();
    Matrix<T> result = Matrix<T>(mRows, mColumns);
    result.make_e_matrix();
    int i = 0;
    while (i < mRows)
    {
        elementary_transf(mat_1, n, mat_res, &i, 1);
    }
    i = n - 1;
    while (i >= 0)
    {
        elementary_transf(mat_1, n, mat_res, &i, -1);
    }
}

template <typename T>
void Matrix<T>::check_reversing_matrix()
{
    if (mRows != m_1)
        //кидаем ошибку
    else
    {
        if (det() == 0)
            //кидаем ошибку
    }
}

template <typename T>
void Matrix<T>::transpose()
{
    //check_non_null
    Matrix<T> tmp = Matrix(mColumns, mRows);
    for (int i = 0; i < mRows; i++)
        for (int j = 0; j < mColumns; j++)
            tmp[j][i] = this[i][j];
    move(tmp);
}

template <typename T>
Matrix<T>& Matrix<T>::operator =(std::initializer_list<std::initializer_list<T>> list)
{
    size_t rows = list.size();
    auto it = list.begin();
    size_t columns = it->size();
    //check
    allocateMatrix(rows, columns);
    size_t i = 0;
    for (const auto &row : list)
    {
        size_t j = 0;
        for (const auto &column : row)
        {
            this[i][j] = column;
            j++;
        }
        i++;
    }
    return *this;
}

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
T& Matrix<T>::operator ()(int i, int j)
{
    //check
    return this[i][j];
}
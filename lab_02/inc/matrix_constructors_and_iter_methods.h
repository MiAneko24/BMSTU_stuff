#ifndef MATRIX_CONSTRUCTORS_AND_ITER_METHODS
#define MATRIX_CONSTRUCTORS_AND_ITER_METHODS
#include "matrix_templates.h"

template <typename T>
Matrix<T>::~Matrix()
{
    reset();
}


template <typename T>
MatrixRow<T>& Matrix<T>::operator[](int pos)
{
    checkRowIndex(pos, __FILE__, __LINE__);
    return data[pos];
}

template <typename T>
void Matrix<T>::move(Matrix<T> &&matrix)
{
    allocateMatrix(matrix.getRows(), matrix.getColumns());
    for (int i = 0; i < mRows; i++)
        for (int j = 0; j < mColumns; j++)
            this->operator[](i)[j] = matrix[i][j];
    matrix.reset();
}

template <typename T>
void Matrix<T>::move(Matrix<T> &matrix)
{
    allocateMatrix(matrix.getRows(), matrix.getColumns());
    for (int i = 0; i < mRows; i++)
        for (int j = 0; j < mColumns; j++)
            this->operator[](i)[j] = matrix[i][j];
    matrix.reset();
}

template <typename T>
void Matrix<T>::copy(Matrix<T> &matrix)
{
    allocateMatrix(matrix.getRows(), matrix.getColumns());
    for (int i = 0; i < mRows; i++)
        for (int j = 0; j < mColumns; j++)
            this->operator[](i)[j] = matrix[i][j];
}

template <typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> list)
{
    checkList(list, __FILE__, __LINE__);
    size_t rows = list.size();
    auto it = list.begin();
    size_t columns = it->size();
    
    allocateDataArray(rows, columns);
    size_t i = 0;
    for (const auto &row : list)
    {
        this->operator[](i) = MatrixRow<T>(row, mColumns);
        i++;
    }
}

template <typename T>
T& Matrix<T>::get_elem(int i, int j)
{
    return this->operator[](i)[j];
}

template <typename T>
void Matrix<T>::set_elem(int i, int j, int num)
{
    checkIndexes(i, j, __FILE__, __LINE__);
    this->operator[](i)[j] = num;
}

template <typename T>
void Matrix<T>::allocateDataArray(size_t rows, size_t columns)
{
    mRows = rows;
    mColumns = columns;
    checkNull(__FILE__, __LINE__);
    try
    {
        reset(mRows);
    }
    catch(const std::bad_alloc)
    {
        time_t time_cur = time(nullptr);
        throw MemoryError(ctime(&time_cur), __FILE__, typeid(*this).name(), __LINE__, "Failed memory allocation");
    }
}

template <typename T>
void Matrix<T>::allocateMatrix(size_t rows, size_t columns)
{
    allocateDataArray(rows, columns);
    
    for (int i = 0; i < mRows; i++)
    {
        operator[](i).allocateMatrixRow(mColumns);
    }
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
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            this->operator[](i)[j] = fill_with;
}

template <typename T>
Matrix<T>::Matrix(T **source, size_t rows, size_t columns)
{
    checkMatrixSource(source, __FILE__, __LINE__);
    allocateMatrix(rows, columns);
    for (int i = 0; i < mRows; i++)
        for (int j = 0; j < mColumns; j++)
            this->operator[](i)[j] = source[i][j];
}

template <typename T>
Matrix<T>::Matrix(Matrix<T> &matrix)
{
    copy(matrix);
}

template <typename T>
void Matrix<T>::reset()
{
    if (data)
    {
        for (int i = 0; i < mRows; i++)
            this->operator[](i).reset();
        data.reset();
    }
}

template <typename T>
void Matrix<T>::reset(size_t size)
{
    reset();
    data.reset(new MatrixRow<T>[mRows]);
}

template <typename T>
Matrix<T>::Matrix(Matrix<T> &&matrix)
{
    move(matrix);
}

template <typename T>
Iterator<T> Matrix<T>::begin()
{
    Iterator<T> iter = Iterator<T>((*this), 0);
    return  iter;
}

template <typename T>
Iterator<T> Matrix<T>::end()
{
    Iterator<T> iter = Iterator<T>((*this), mRows * mColumns);
    return  iter;
}

template <typename T>
constIterator<T> Matrix<T>::begin() const
{
    constIterator<T> iter = constIterator<T>((*this), 0);
    return  iter;
}

template <typename T>
constIterator<T> Matrix<T>::end() const
{
    constIterator<T> iter = constIterator<T>((*this), mRows * mColumns);
    return  iter;
}

template <typename T>
constIterator<T> Matrix<T>::cbegin() const
{
    constIterator<T> iter = constIterator<T>((*this), 0);
    return  iter;
}

template <typename T>
constIterator<T> Matrix<T>::cend() const
{
    constIterator<T> iter = constIterator<T>((*this), mRows * mColumns);
    return  iter;
}


#endif
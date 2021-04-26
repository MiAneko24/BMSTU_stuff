#ifndef MATRIX_ROW_METHODS_H
#define MATRIX_ROW_METHODS_H
#include "matrix_row.h"

template <typename T>
MatrixRow<T>::MatrixRow(size_t size)
{
    allocateMatrixRow(size);
}

template <typename T>
bool MatrixRow<T>::operator !=(MatrixRow<T> &matRow)
{
    bool result = false;
    for (int i = 0; i < rSize && !result; i++)
        if (this->operator[](i) != matRow[i])
            result = true;
    return result;
}

template<>
bool MatrixRow<double>::operator !=(MatrixRow<double> &matRow)
{
    bool result = false;
    for (int i = 0; i < rSize && !result; i++)
        if (abs(this->operator[](i) - matRow[i]) > EPS)
            result = true;
    return result;
}


template <typename T>
bool MatrixRow<T>::operator ==(MatrixRow<T> &matRow)
{
    bool result = true;
    for (int i = 0; i < rSize && result; i++)
        if (this->operator[](i) != matRow[i])
            result = false;
    return result;
}

template<>
bool MatrixRow<double>::operator ==(MatrixRow<double> &matRow)
{
    bool result = true;
    for (int i = 0; i < rSize && result; i++)
        if (abs(this->operator[](i) - matRow[i]) > EPS)
            result = false;
    return result;
}

template <typename T>
size_t MatrixRow<T>::getSize()
{
    return rSize;
}

template <typename T>
void MatrixRow<T>::checkNull(T *array)
{
    if (array == nullptr)
    {

        time_t time_cur = time(nullptr);
        throw NullPointerError(ctime(&time_cur), __FILE__, typeid(*this).name(), __LINE__, "Attempt of creating void line");
    }
}

template <typename T>
void MatrixRow<T>::reset()
{
    if (array)
        array.reset();
}

template <typename T>
MatrixRow<T>::MatrixRow(std::initializer_list<T> list, size_t columns)
{
    checkList(list, columns);
    allocateMatrixRow(columns);
    size_t i = 0;
    for (T elem : list)
    {
        this->operator[](i) = elem;
        i++; 
    }
};

template <typename T>
void MatrixRow<T>::checkList(std::initializer_list<T> list, size_t columns)
{
    if (columns != list.size())
    {
        time_t time_cur = time(nullptr);
        throw NullPointerError(ctime(&time_cur), __FILE__, typeid(*this).name(), __LINE__, "It is impossible to create a matrix with different amount of columns in a row");
    }
}

template <typename T>
void MatrixRow<T>::allocateMatrixRow(size_t size)
{
    rSize = size;
    try
    {
        T *new_array = new T[size]{};
        array.reset(new_array);
    }
    catch(const std::bad_alloc)
    {
        time_t time_cur = time(nullptr);
        throw MemoryError(ctime(&time_cur), __FILE__, typeid(*this).name(), __LINE__, "Failed memory allocation");
    }
    
}

template <typename T>
T& MatrixRow<T>::operator[](size_t column) const
{
    checkIndex(column);
    return array[column];
}

template <typename T>
void MatrixRow<T>::checkIndex(int pos) const
{
    if (pos >= rSize || pos < 0)
    {
        time_t time_cur = time(nullptr);
        throw IndexError(ctime(&time_cur), __FILE__, typeid(*this).name(), __LINE__, "Index of columns is out of range");
    }
}

template <typename T>
void MatrixRow<T>::copy(const MatrixRow<T> &matRow)
{
    size_t size = matRow.rSize;
    allocateMatrixRow(size);
    for (int i = 0; i < rSize; i++)
        this->operator[](i) = matRow[i];
}

template <typename T>
void MatrixRow<T>::move(MatrixRow<T> &&matRow)
{
    allocateMatrixRow(matRow.getSize());
    for (int i = 0; i < rSize; i++)
        this->operator[](i) = matRow[i];
    matRow.reset();
}


template <typename T>
void MatrixRow<T>::move(MatrixRow<T> &matRow)
{
    allocateMatrixRow(matRow.getSize());
    for (int i = 0; i < rSize; i++)
        this->operator[](i) = matRow[i];
    matRow.reset();
}

template <typename T>
MatrixRow<T>::MatrixRow(const MatrixRow<T> &matRow)
{
    copy(matRow);
}

template <typename T>
MatrixRow<T> MatrixRow<T>::operator =(MatrixRow<T> &matRow)
{
    copy(matRow);
    return *this;
}

template <typename T>
MatrixRow<T>& MatrixRow<T>::operator =(MatrixRow<T> &&matRow)
{
    move(matRow);
    return *this;
}

#endif
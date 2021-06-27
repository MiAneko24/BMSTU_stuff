#pragma once
#include "vector.hpp"
#include "matrix.hpp"
#define EPS 1e-7
#include "exceptions.hpp"

template <typename T>
class Matrix;

template <typename T>
Vector<T>::Vector(size_t size)
{
    allocateVector(size);
}

template <typename T>
Vector<T>::Vector(const Vector<T> &vector)
{
    copy(vector);
}

template <typename T>
Vector<T>::Vector(Vector<T> &&vector)
{
    allocateVector(vector.getSize());
    this->rSize = vector.rSize;
    this->array = vector.array;
    vector.reset();
}

// template <typename T>
// void Vector<T>::checkSizes(Matrix<T> &matrix)

template <typename T>
void Vector<T>::checkSizes(const Matrix<T> &matrix, std::string file, int line) const
{
    if (rSize != matrix.getRows())
    {
        time_t time_cur = time(nullptr);
        throw DimensionMatrixError(ctime(&time_cur), file, typeid(*this).name(), line, "It is impossible to multiply a vector on matrix with different amount of rows");
    }
}


template <typename T>
Vector<T> Vector<T>::operator *(const Matrix<T> &matrix) const
{
    checkSizes(matrix, __FILE__, __LINE__);

    Vector<T> result = Vector<T>(matrix.getColumns());
    for (int i = 0; i < rSize; i++)
    {
        for (int j = 0; j < matrix.getColumns(); j++)
            result[i] += this->operator[](j) * matrix[j][i];
    }
    return result;
}

template <typename T>
Vector<T>& Vector<T>::operator *=(const Matrix<T> &matrix)
{
    checkSizes(matrix, __FILE__, __LINE__);
    Vector<T> result = Vector<T>(matrix.getColumns());
    for (int i = 0; i < rSize; i++)
    {
        for (int j = 0; j < matrix.getColumns(); j++)
            result[i] += (*this)[j] * matrix[j][i];
    }
    (*this) = result;
    return (*this);
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> list, size_t columns)
{
    checkList(list, columns, __FILE__, __LINE__);
    allocateVector(columns);
    size_t i = 0;
    for (T elem : list)
    {
        this->operator[](i) = elem;
        i++; 
    }
};

template <typename T>
Vector<T>::Vector(T *t_array, size_t t_size)
{
    rSize = t_size;
    array.reset(t_array);
}

template <typename T>
void Vector<T>::allocateVector(size_t size)
{
    rSize = size;
    try
    {
        T *new_array = new T[size]{};
        array.reset(new_array);
    }
    catch(const std::bad_alloc& e)
    {
        time_t time_cur = time(nullptr);
        throw MemoryError(ctime(&time_cur), __FILE__, typeid(*this).name(), __LINE__, "Failed memory allocation");
    } 
}


template <typename T>
void Vector<T>::copy(const Vector<T> &vector)
{
    size_t size = vector.rSize;
    allocateVector(size);
    for (size_t i = 0; i < rSize; i++)
        this->operator[](i) = vector[i];
}


template <typename T>
void Vector<T>::move(Vector<T> &&vector)
{
    allocateVector(vector.getSize());
    this->rSize = vector.rSize;
    this->array = vector.array;
    vector.reset();
}


template <typename T>
void Vector<T>::add(const T &obj)
{
    Vector<T> tmp = *this;
    allocateVector(rSize + 1);
    for (int i = 0; i < tmp.rSize; i++)
    {
        this->operator[](i) = tmp[i];
    }
    this->operator[](rSize - 1) = obj;
    tmp.reset();
}


template <typename T>
Vector<T>& Vector<T>::operator =(Vector<T> &&vector)
{
    allocateVector(vector.getSize());
    this->rSize = vector.rSize;
    this->array = vector.array;
    vector.reset();
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator =(const Vector<T> &vector)
{
    copy(vector);
    return *this;
}

template <typename T>
bool Vector<T>::operator ==(const Vector<T> &vector) const noexcept
{
    bool result = true;
    for (int i = 0; i < rSize && result; i++)
        if (this->operator[](i) != vector[i])
            result = false;
    return result;
}

template <typename T>
bool Vector<T>::operator !=(const Vector<T> &vector) const noexcept
{
    bool result = false;
    for (int i = 0; i < rSize && !result; i++)
        if (this->operator[](i) != vector[i])
            result = true;
    return result;
}


template <typename T>
T& Vector<T>::operator[](size_t column)
{
    checkIndex(column, __FILE__, __LINE__);
    return array[column];
}

template <typename T>
const T& Vector<T>::operator[](size_t column) const
{
    checkIndex(column, __FILE__, __LINE__);
    return array[column];
}

template <typename T>
size_t Vector<T>::getSize() const noexcept
{
    return rSize;
}

template <typename T>
void Vector<T>::reset() noexcept
{
    if (array)
        array.reset();
}

template <typename T>
void Vector<T>::remove(VectorIterator<T> &del)
{
    Vector<T> tmp = Vector<T>(rSize - 1);
    int j = 0;
    for (VectorIterator<T> i = begin(); !(i.isEnd()); i++)
    {
        if (i != del)
        {
            tmp[j] = *i;
            j++;
        }
    }
    move(std::move(tmp));
}

template <typename T>
VectorIterator<T> Vector<T>::begin()
{
    return VectorIterator<T>((*this), 0);
}

template <typename T>
VectorIterator<T> Vector<T>::end()
{
    return VectorIterator<T>((*this), rSize);
}

template <typename T>
VectorConstIterator<T> Vector<T>::begin() const
{
    return VectorConstIterator<T>((*this), 0);
}

template <typename T>
VectorConstIterator<T> Vector<T>::end() const
{
    return VectorConstIterator<T>((*this), rSize);
}

template <typename T>
void Vector<T>::checkIndex(int pos, std::string file, int line) const
{
    if (pos >= rSize || pos < 0)
    {
        time_t time_cur = time(nullptr);
        throw IndexError(ctime(&time_cur), file, typeid(*this).name(), line, "Index of columns is out of range");
    }
}

template <typename T>
void Vector<T>::checkList(std::initializer_list<T> list, size_t columns, std::string file, int line) const
{
    if (columns != list.size())
    {
        time_t time_cur = time(nullptr);
        throw NullPointerError(ctime(&time_cur), file, typeid(*this).name(), line, "It is impossible to create a matrix with different amount of columns in a row");
    }
}

template <typename T>
void Vector<T>::checkNull(T *array, std::string file, int line) const
{
    if (array == nullptr)
    {
        time_t time_cur = time(nullptr);
        throw NullPointerError(ctime(&time_cur), file, typeid(*this).name(), line, "Attempt of creating void line");
    }
}

template <typename T>
Vector<T>& Vector<T>::operator =(std::initializer_list<T> list)
{
    auto it = list.begin();
    size_t columns = list.size();
    allocateVector(columns);
    int i = 0;
    for (const auto &elem : list)
    {
        (*this)[i] = elem;
        i++;
    }
    return *this;
}
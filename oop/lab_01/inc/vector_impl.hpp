#ifndef MATRIX_ROW_METHODS_HPP
#define MATRIX_ROW_METHODS_HPP
#include "vector.hpp"
#define EPS 1e-7

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
void Vector<T>::checkSizes(Matrix<T> &matrix, std::string file, int line)
{
    if (rSize != matrix.getRows())
    {
        time_t time_cur = time(nullptr);
        throw DimensionMatrixError(ctime(&time_cur), file, typeid(*this).name(), line, "It is impossible to multiply a vector on matrix with different amount of rows");
    }
}

template <typename T>
Vector<T> Vector<T>::operator *(Matrix<T> &matrix)
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
Vector<T>::Vector(std::initializer_list<T> list, size_t columns)
{
    checkList(list, columns);
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
    catch(const std::bad_alloc)
    {
        time_t time_cur = time(nullptr);
        throw MemoryError(ctime(&time_cur), __FILE__, typeid(*this).name(), __LINE__, "Failed memory allocation");
    } 
}

template <typename T>
void Vector<T>::copy(Vector<T> &vector)
{
    size_t size = vector.rSize;
    allocateVector(size);
    for (int i = 0; i < rSize; i++)
        this->operator[](i) = vector[i];
}

template <typename T>
void Vector<T>::copy(const Vector<T> &vector)
{
    size_t size = vector.rSize;
    allocateVector(size);
    for (int i = 0; i < rSize; i++)
        this->operator[](i) = vector[i];
}

template <typename T>
void Vector<T>::move(Vector<T> &vector)
{
    allocateVector(vector.getSize());
    for (int i = 0; i < rSize; i++)
        this->operator[](i) = vector[i];
    vector.reset();
}

template <typename T>
void Vector<T>::move(Vector<T> &&vector)
{
    allocateVector(vector.getSize());
    for (int i = 0; i < rSize; i++)
        this->operator[](i) = vector[i];
    vector.reset();
}

template <typename T>
void Vector<T>::move(const Vector<T> &vector)
{
    allocateVector(vector.getSize());
    for (int i = 0; i < rSize; i++)
        this->operator[](i) = vector[i];
    vector.reset();
}

template <typename T>
void Vector<T>::move(const Vector<T> &&vector)
{
    allocateVector(vector.getSize());
    for (int i = 0; i < rSize; i++)
        this->operator[](i) = vector[i];
    vector.reset();
}

template <typename T>
Vector<T> Vector<T>::operator =(Vector<T> &vector)
{
    copy(vector);
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator =(Vector<T> &&vector)
{
    move(vector);
    return *this;
}

template <typename T>
Vector<T> Vector<T>::operator =(const Vector<T> &vector)
{
    copy(vector);
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator =(const Vector<T> &&vector)
{
    move(vector);
    return *this;
}

template <typename T>
bool Vector<T>::operator ==(Vector<T> &vector) const noexcept
{
    bool result = true;
    for (int i = 0; i < rSize && result; i++)
        if (this->operator[](i) != vector[i])
            result = false;
    return result;
}

template <typename T>
bool Vector<T>::operator !=(Vector<T> &vector) const noexcept
{
    bool result = false;
    for (int i = 0; i < rSize && !result; i++)
        if (this->operator[](i) != vector[i])
            result = true;
    return result;
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

template <>
bool Vector<double>::operator !=(Vector<double> &vector) const noexcept
{
    bool result = false;
    for (int i = 0; i < rSize && !result; i++)
        if (abs(this->operator[](i) - vector[i]) > EPS)
            result = true;
    return result;
}

template<>
bool Vector<double>::operator ==(Vector<double> &vector) const noexcept
{
    bool result = true;
    for (int i = 0; i < rSize && result; i++)
        if (abs(this->operator[](i) - vector[i]) > EPS)
            result = false;
    return result;
}

template <typename T>
T& Vector<T>::operator[](size_t column) const
{
    checkIndex(column);
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
void Vector<T>::checkIndex(int pos, std::string file, int line) const
{
    if (pos >= rSize || pos < 0)
    {
        time_t time_cur = time(nullptr);
        throw IndexError(ctime(&time_cur), file, typeid(*this).name(), line, "Index of columns is out of range");
    }
}

template <typename T>
void Vector<T>::checkList(std::initializer_list<T> list, size_t columns, std::string file, int line)
{
    if (columns != list.size())
    {
        time_t time_cur = time(nullptr);
        throw NullPointerError(ctime(&time_cur), file, typeid(*this).name(), line, "It is impossible to create a matrix with different amount of columns in a row");
    }
}

template <typename T>
void Vector<T>::checkNull(T *array, std::string file, int line)
{
    if (array == nullptr)
    {
        time_t time_cur = time(nullptr);
        throw NullPointerError(ctime(&time_cur), file, typeid(*this).name(), line, "Attempt of creating void line");
    }
}

#endif
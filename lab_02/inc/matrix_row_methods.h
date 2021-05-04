#ifndef MATRIX_ROW_METHODS_H
#define MATRIX_ROW_METHODS_H
#include "matrix_templates.h"
#define EPS 1e-7

template <typename T>
Matrix<T>::MatrixRow::MatrixRow(size_t size)
{
    allocateMatrixRow(size);
}

template <typename T>
Matrix<T>::MatrixRow::MatrixRow(const Matrix<T>::MatrixRow &matRow)
{
    copy(matRow);
}

template <typename T>
Matrix<T>::MatrixRow::MatrixRow(std::initializer_list<T> list, size_t columns)
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
Matrix<T>::MatrixRow::MatrixRow(T *t_array, size_t t_size)
{
    rSize = t_size;
    array.reset(t_array);
}

template <typename T>
void Matrix<T>::MatrixRow::allocateMatrixRow(size_t size)
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
void Matrix<T>::MatrixRow::copy(Matrix<T>::MatrixRow &matRow)
{
    size_t size = matRow.rSize;
    allocateMatrixRow(size);
    for (int i = 0; i < rSize; i++)
        this->operator[](i) = matRow[i];
}

template <typename T>
void Matrix<T>::MatrixRow::copy(const Matrix<T>::MatrixRow &matRow)
{
    size_t size = matRow.rSize;
    allocateMatrixRow(size);
    for (int i = 0; i < rSize; i++)
        this->operator[](i) = matRow[i];
}

template <typename T>
void Matrix<T>::MatrixRow::move(Matrix<T>::MatrixRow &matRow)
{
    allocateMatrixRow(matRow.getSize());
    for (int i = 0; i < rSize; i++)
        this->operator[](i) = matRow[i];
    matRow.reset();
}

template <typename T>
void Matrix<T>::MatrixRow::move(Matrix<T>::MatrixRow &&matRow)
{
    allocateMatrixRow(matRow.getSize());
    for (int i = 0; i < rSize; i++)
        this->operator[](i) = matRow[i];
    matRow.reset();
}

template <typename T>
void Matrix<T>::MatrixRow::move(const Matrix<T>::MatrixRow &matRow)
{
    allocateMatrixRow(matRow.getSize());
    for (int i = 0; i < rSize; i++)
        this->operator[](i) = matRow[i];
    matRow.reset();
}

template <typename T>
void Matrix<T>::MatrixRow::move(const Matrix<T>::MatrixRow &&matRow)
{
    allocateMatrixRow(matRow.getSize());
    for (int i = 0; i < rSize; i++)
        this->operator[](i) = matRow[i];
    matRow.reset();
}

template <typename T>
typename Matrix<T>::MatrixRow Matrix<T>::MatrixRow::operator =(Matrix<T>::MatrixRow &matRow)
{
    copy(matRow);
    return *this;
}

template <typename T>
typename Matrix<T>::MatrixRow& Matrix<T>::MatrixRow::operator =(Matrix<T>::MatrixRow &&matRow)
{
    move(matRow);
    return *this;
}

template <typename T>
typename Matrix<T>::MatrixRow Matrix<T>::MatrixRow::operator =(const Matrix<T>::MatrixRow &matRow)
{
    copy(matRow);
    return *this;
}

template <typename T>
typename Matrix<T>::MatrixRow& Matrix<T>::MatrixRow::operator =(const Matrix<T>::MatrixRow &&matRow)
{
    move(matRow);
    return *this;
}

template <typename T>
bool Matrix<T>::MatrixRow::operator ==(Matrix<T>::MatrixRow &matRow) const noexcept
{
    bool result = true;
    for (int i = 0; i < rSize && result; i++)
        if (this->operator[](i) != matRow[i])
            result = false;
    return result;
}

template <typename T>
bool Matrix<T>::MatrixRow::operator !=(Matrix<T>::MatrixRow &matRow) const noexcept
{
    bool result = false;
    for (int i = 0; i < rSize && !result; i++)
        if (this->operator[](i) != matRow[i])
            result = true;
    return result;
}

template <typename T>
bool Matrix<T>::MatrixRow::operator ==(const Matrix<T>::MatrixRow &matRow) const noexcept
{
    bool result = true;
    for (int i = 0; i < rSize && result; i++)
        if (this->operator[](i) != matRow[i])
            result = false;
    return result;
}

template <typename T>
bool Matrix<T>::MatrixRow::operator !=(const Matrix<T>::MatrixRow &matRow) const noexcept
{
    bool result = false;
    for (int i = 0; i < rSize && !result; i++)
        if (this->operator[](i) != matRow[i])
            result = true;
    return result;
}

template <>
bool Matrix<double>::MatrixRow::operator !=(Matrix<double>::MatrixRow &matRow) const noexcept
{
    bool result = false;
    for (int i = 0; i < rSize && !result; i++)
        if (abs(this->operator[](i) - matRow[i]) > EPS)
            result = true;
    return result;
}

template<>
bool Matrix<double>::MatrixRow::operator ==(Matrix<double>::MatrixRow &matRow) const noexcept
{
    bool result = true;
    for (int i = 0; i < rSize && result; i++)
        if (abs(this->operator[](i) - matRow[i]) > EPS)
            result = false;
    return result;
}

template <typename T>
T& Matrix<T>::MatrixRow::operator[](size_t column) const
{
    checkIndex(column);
    return array[column];
}

template <typename T>
size_t Matrix<T>::MatrixRow::getSize() const noexcept
{
    return rSize;
}

template <typename T>
void Matrix<T>::MatrixRow::reset() noexcept
{
    if (array)
        array.reset();
}

template <typename T>
void Matrix<T>::MatrixRow::checkIndex(int pos, std::string file, int line) const
{
    if (pos >= rSize || pos < 0)
    {
        time_t time_cur = time(nullptr);
        throw IndexError(ctime(&time_cur), file, typeid(*this).name(), line, "Index of columns is out of range");
    }
}

template <typename T>
void Matrix<T>::MatrixRow::checkList(std::initializer_list<T> list, size_t columns, std::string file, int line)
{
    if (columns != list.size())
    {
        time_t time_cur = time(nullptr);
        throw NullPointerError(ctime(&time_cur), file, typeid(*this).name(), line, "It is impossible to create a matrix with different amount of columns in a row");
    }
}

template <typename T>
void Matrix<T>::MatrixRow::checkNull(T *array, std::string file, int line)
{
    if (array == nullptr)
    {
        time_t time_cur = time(nullptr);
        throw NullPointerError(ctime(&time_cur), file, typeid(*this).name(), line, "Attempt of creating void line");
    }
}

#endif
#ifndef MATRIX_TEMPLATES_H
#define MATRIX_TEMPLATES_H

#include <iostream>
#include <string>
#include "base_matrix_class.h"
#include "matrix_row.h"
#include "matrix_exceptions.h"
#include "const_iterator_templates.h"
#include "iterator_template.h"

template <typename T>
class MatrixRow;

template <typename T>
class Matrix : public BaseMatrix 
{
    private:
        std::shared_ptr<MatrixRow<T>[]> data;
        void checkSumSizes(Matrix<T> &matrix, std::string file, int line);
        void checkSquare(std::string file, int line);
        void checkMulSizes(Matrix<T> &mat, std::string file, int line);
        void checkIndexes(int i, int j, std::string file, int line);
        void checkRowIndex(int i, std::string file, int line);
        void checkMatrixSource(T **source, std::string file, int line);
        void checkOperationsType(std::string file, int line);
        void checkDivider(T &elem, std::string file, int line);
        void check_reversing_matrix(std::string file, int line);

        void allocateDataArray(size_t rows, size_t columns);
        void allocateMatrix(size_t rows, size_t columns); 

        void checkDeterminant(std::string file, int line);
        void checkList(std::initializer_list<std::initializer_list<T>> list, std::string file, int line);
        void checkNull(std::string file, int line);
        void checkAddSizes(Matrix<T> &mat, std::string file, int line);

        T determinant_recursive(Matrix<T> &matrix);
        void swap_rows(int i, int j);
        int sign(int i);
        void move(Matrix<T> &&matrix);
        void copy(Matrix<T> &matrix);

        void move(Matrix<T> &matrix);

        void fill_additional_matrix(Matrix<T> &mat, Matrix<T> &tmp, size_t k);
        void elementary_transf(Matrix<T> &mat_res, int &i, int step);
        void reset(size_t size); 
        void reset(); 
        
    public:
        friend Iterator<T>;
        friend constIterator<T>;
        ~Matrix();

        void addEq(Matrix<T> &matrix);
        void subEq(Matrix<T> &matrix);
        void mulEq(T &elem);
        void divEq(T &elem);

        Matrix<T> add(Matrix<T> &mat_1, Matrix<T> &mat_2);

        Matrix<T> add(Matrix<T> &mat); 
        Matrix<T> sub(Matrix<T> &mat); 
        Matrix<T> mul(Matrix<T> &mat); 
        Matrix<T> mul(T &elem);
        Matrix<T> div(T &elem);

        Matrix(std::initializer_list<std::initializer_list<T>> list); 
        explicit Matrix(Matrix<T> &matrix); 
        Matrix(size_t rows, size_t columns); 
        Matrix(T &fill_with, size_t rows, size_t columns); 
        Matrix(T **source, size_t rows, size_t columns); 
        Matrix(Matrix<T> &&matrix);

        Matrix<T> operator *(Matrix<T> &mat); 
        Matrix<T> operator *(T &elem); 
        Matrix<T>& operator *=(T &elem); 
        
        Matrix<T> operator +(Matrix<T> &mat); 
        Matrix<T>& operator +=(Matrix<T> &mat);

        Matrix<T> operator /(T &elem); 
        Matrix<T>& operator /=(T &elem);
        bool operator ==(Matrix<T> &mat);
        bool operator != (Matrix<T> &mat);
        Matrix<T> operator -(Matrix<T> &mat); 
        Matrix<T>& operator -=(Matrix<T> &mat);
        MatrixRow<T>& operator [](int pos); 

        Matrix<T>& operator =(std::initializer_list<std::initializer_list<T>> list);
        Matrix<T>& operator =(Matrix<T> &matrix);
        Matrix<T>& operator =(Matrix<T> &&matrix);
        T& operator ()(int i, int j);
        T& get_elem(int i, int j);
        void set_elem(int i, int j, int num);
        
        T det();
        void transpose();

        void make_e_matrix();

        void reverse_matrix();

        Iterator<T> begin();
        Iterator<T> end();

        constIterator<T> begin() const;
        constIterator<T> end() const;
        constIterator<T> cbegin() const;
        constIterator<T> cend() const;
};

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
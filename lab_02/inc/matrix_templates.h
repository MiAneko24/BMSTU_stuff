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
        void checkSumSizes(Matrix<T> &matrix);
        void checkSquare();
        void checkMulSizes(Matrix<T> &mat);
        void checkIndexes(int i, int j);
        void checkRowIndex(int i);
        void checkColumnIndex(int j);
        void checkMatrixSource(T **source);
        void checkOperationsType();
        void checkDivider(T &elem);

        void allocateDataArray(size_t rows, size_t columns);
        void allocateMatrix(size_t rows, size_t columns); //DONE

        void checkDeterminant();
        void checkList(std::initializer_list<std::initializer_list<T>> list);
        void checkNull();
        void checkAddSizes(Matrix<T> &mat);

        T determinant_recursive(Matrix<T> &matrix);
        void swap_rows(int i, int j);
        int sign(int i);
        void move(Matrix<T> &&matrix);
        void copy(Matrix<T> &matrix);

        void move(Matrix<T> &matrix);

        void fill_additional_matrix(Matrix<T> &mat, Matrix<T> &tmp, size_t k);
        void elementary_transf(Matrix<T> &mat_res, int &i, int step);
        void check_reversing_matrix();
        void reset(size_t size); //DONE
        void reset(); //DONE
        
    public:
        friend Iterator<T>;
        friend constIterator<T>;
        ~Matrix();

        void addEq(Matrix<T> &matrix);
        void subEq(Matrix<T> &matrix);
        void mulEq(T &elem);
        void divEq(T &elem);

        Matrix<T> add(Matrix<T> &mat_1, Matrix<T> &mat_2);

        Matrix<T> add(Matrix<T> &mat); // checked \/
        Matrix<T> sub(Matrix<T> &mat); // checked \/
        Matrix<T> mul(Matrix<T> &mat); // checked \/
        Matrix<T> mul(T &elem);
        Matrix<T> div(T &elem);

        Matrix(std::initializer_list<std::initializer_list<T>> list); //DONE
        explicit Matrix(Matrix<T> &matrix); //DONE
        Matrix(size_t rows, size_t columns); //DONE
        Matrix(T &fill_with, size_t rows, size_t columns); //DONE
        Matrix(T **source, size_t rows, size_t columns); //DONE
        Matrix(Matrix<T> &&matrix);

        Matrix<T> operator *(Matrix<T> &mat); //DONE, checked
        Matrix<T> operator *(T &elem); //DONE
        Matrix<T>& operator *=(T &elem); 
        
        Matrix<T> operator +(Matrix<T> &mat); //DONE, checked
        Matrix<T>& operator +=(Matrix<T> &mat);

        Matrix<T> operator /(T &elem); //DONE
        Matrix<T>& operator /=(T &elem);
        bool operator ==(Matrix<T> &mat);
        bool operator != (Matrix<T> &mat);
        Matrix<T> operator -(Matrix<T> &mat); //DONE, checked
        Matrix<T>& operator -=(Matrix<T> &mat);
        MatrixRow<T>& operator [](int pos); //DONE

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
    checkRowIndex(pos);
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
    checkList(list);
    size_t rows = list.size();
    auto it = list.begin();
    size_t columns = it->size();
    // printf("at alloc, rows= %ld, columns=%ld\n", rows, columns);
    
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
    checkIndexes();
    this->operator[](i)[j] = num;
}

// template <typename T>
// void Matrix<T>::checkIndexes(int i, int j)
// {
//     checkRowIndex(i);
//     checkColumnIndex(j);
// }

template <typename T>
void Matrix<T>::allocateDataArray(size_t rows, size_t columns)
{
    mRows = rows;
    mColumns = columns;
    checkNull();
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
        // printf("i = %d\n", i);
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
    checkMatrixSource(source);
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
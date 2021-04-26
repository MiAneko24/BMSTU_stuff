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
};

#include "matrix_constructors_and_iter_methods.h"
#include "math_operations.h"
#include "matrix_checks.h"

#endif
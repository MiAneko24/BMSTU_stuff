#ifndef MATRIX_TEMPLATES_H
#define MATRIX_TEMPLATES_H

#include <iostream>
#include <string>
#include "base_matrix_class.h"
#include "matrix_exceptions.h"
#include "const_iterator_templates.h"
#include "iterator_template.h"

template <typename T>
class Matrix : public BaseMatrix 
{        
    class MatrixRow;
    friend Iterator<T>;
    friend constIterator<T>;

    public:
        
        Matrix(size_t rows, size_t columns); 
        explicit Matrix(const Matrix<T> &matrix); 
        Matrix(Matrix<T> &&matrix) noexcept; 

        Matrix(std::initializer_list<std::initializer_list<T>> list); 
        Matrix(T &fill_with, size_t rows, size_t columns); 
        Matrix(T **source, size_t rows, size_t columns); 

        void move(Matrix<T> &matrix) noexcept;
        void move(Matrix<T> &&matrix) noexcept;

        void move(const Matrix<T> &matrix) noexcept;
        void move(const Matrix<T> &&matrix) noexcept;

        void copy(Matrix<T> &matrix);

        void copy(const Matrix<T> &matrix);

        Matrix<T>& operator =(Matrix<T> &matrix);
        Matrix<T>& operator =(Matrix<T> &&matrix);

        Matrix<T>& operator =(const Matrix<T> &matrix);
        Matrix<T>& operator =(const Matrix<T> &&matrix);

        Matrix<T>& operator =(std::initializer_list<std::initializer_list<T>> list);

        Matrix<T> add(Matrix<T> &mat); 
        Matrix<T> operator +(Matrix<T> &mat); 

        Matrix<T> add(const Matrix<T> &mat); 
        Matrix<T> operator +(const Matrix<T> &mat); 
        
        void addEq(Matrix<T> &matrix);
        Matrix<T>& operator +=(Matrix<T> &mat);

        void addEq(const Matrix<T> &matrix);
        Matrix<T>& operator +=(const Matrix<T> &mat);
        
        Matrix<T> sub(Matrix<T> &mat); 
        Matrix<T> operator -(Matrix<T> &mat); 

        Matrix<T> sub(const Matrix<T> &mat); 
        Matrix<T> operator -(const Matrix<T> &mat); 

        void subEq(Matrix<T> &matrix);
        Matrix<T>& operator -=(Matrix<T> &mat);

        void subEq(const Matrix<T> &matrix);
        Matrix<T>& operator -=(const Matrix<T> &mat);

        Matrix<T> mul(Matrix<T> &mat); 
        Matrix<T> operator *(Matrix<T> &mat); 

        Matrix<T> mul(const Matrix<T> &mat); 
        Matrix<T> operator *(const Matrix<T> &mat); 

        Matrix<T> mul(T &elem);
        Matrix<T> operator *(T &elem); 

        Matrix<T> mul(const T &elem);
        Matrix<T> operator *(const T &elem);

        void mulEq(T &elem);
        Matrix<T>& operator *=(T &elem); 
        
        void mulEq(const T &elem);
        Matrix<T>& operator *=(const T &elem); 

        Matrix<T> div(T &elem);
        Matrix<T> operator /(T &elem); 

        Matrix<T> div(const T &elem);
        Matrix<T> operator /(const T &elem); 
        
        void divEq(T &elem);
        Matrix<T>& operator /=(T &elem);   
        
        void divEq(const T &elem);
        Matrix<T>& operator /=(const T &elem);        

        bool operator ==(Matrix<T> &mat) noexcept;
        bool operator != (Matrix<T> &mat) noexcept;
        
        bool operator ==(const Matrix<T> &mat) noexcept;
        bool operator != (const Matrix<T> &mat) noexcept;


        MatrixRow& operator [](int pos); 
        T& operator ()(int i, int j);

        T& get_elem(int i, int j);
        void set_elem(int i, int j, int num);
        

        T det();
        
        Matrix<T> transpose();

        Matrix<T> reverse_matrix();

        void make_e_matrix();

        Iterator<T> begin() noexcept;
        Iterator<T> end() noexcept;

        constIterator<T> begin() const noexcept;
        constIterator<T> end() const noexcept;
        constIterator<T> cbegin() const noexcept;
        constIterator<T> cend() const noexcept;

        ~Matrix() noexcept;

     private:
        std::shared_ptr<MatrixRow[]> data;
        
        void checkMatrixSource(T **source, std::string file, int line);
        void checkList(std::initializer_list<std::initializer_list<T>> list, std::string file, int line);
        void checkNull(std::string file, int line);

        void allocateDataArray(size_t rows, size_t columns);
        void allocateMatrix(size_t rows, size_t columns); 
        
        void checkIndexes(int i, int j, std::string file, int line);
        void checkRowIndex(int i, std::string file, int line);

        void checkOperationsType(std::string file, int line);
        
        void checkSquare(std::string file, int line);
        void checkAddSizes(Matrix<T> &mat, std::string file, int line);
        void checkMulSizes(Matrix<T> &mat, std::string file, int line);
        
        void checkDivider(T &elem, std::string file, int line);
        
        void check_reversing_matrix(std::string file, int line);

        void checkDeterminant(std::string file, int line);

        T determinant_recursive(Matrix<T> &matrix);
        
        void swap_rows(int i, int j);
        
        int sign(int i);

        void fill_additional_matrix(Matrix<T> &tmp, Matrix<T> &mat,size_t k) noexcept;
        void elementary_transf(Matrix<T> &mat_res, int &i, int step);
        
        void reset() noexcept; 
        void reset(size_t size) noexcept; 
};

template <typename T>
class Matrix<T>::MatrixRow 
{
    public:
        MatrixRow() : array(nullptr), rSize(0) {};
        MatrixRow(size_t size);
        MatrixRow(const MatrixRow &matRow);
        MatrixRow(std::initializer_list<T> list, size_t columns);
        MatrixRow(T *t_array, size_t t_size);

        void allocateMatrixRow(size_t size);

        void copy(MatrixRow &matRow);
        
        void copy(const MatrixRow &matRow);

        void move(MatrixRow &matRow) noexcept;
        void move(MatrixRow &&matRow) noexcept;
        
        void move(const MatrixRow &matRow) noexcept;
        void move(const MatrixRow &&matRow) noexcept;
        
        MatrixRow operator =(MatrixRow &matRow);
        MatrixRow& operator =(MatrixRow &&matRow);


        MatrixRow operator =(const MatrixRow &matRow);
        MatrixRow& operator =(const MatrixRow &&matRow);
        
        bool operator ==(MatrixRow &matRow) noexcept;
        bool operator !=(MatrixRow &matRow) noexcept;

        bool operator ==(const MatrixRow &matRow) noexcept;
        bool operator !=(const MatrixRow &matRow) noexcept;

        T& operator[](size_t column) const; 

        size_t getSize() const noexcept;
        
        void reset() noexcept;
        
        ~MatrixRow(){};   
        
    private:
        std::shared_ptr<T[]> array = nullptr;
        size_t rSize = 0;
        
        void checkIndex(int pos, std::string file, int line) const;
        void checkList(std::initializer_list<T> list, size_t columns, std::string file, int line);
        void checkNull(T *array, std::string file, int line);
};

#include "matrix_constructors_and_iter_methods.h"
#include "matrix_row_methods.h"
#include "math_operations.h"
#include "matrix_checks.h"

#endif
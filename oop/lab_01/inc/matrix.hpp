#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <iostream>
#include <string>
#include "base_matrix_class.hpp"
// #include "matrix_exceptions.h"
// #include "const_iterator_templates.h"
// #include "iterator_template.h"

template <typename T>
class Vector;

template <typename T>
class Matrix : public BaseMatrix 
{        
    friend Iterator<T>;
    friend constIterator<T>;

    public:
        
        Matrix(size_t rows, size_t columns); 
        explicit Matrix(const Matrix<T> &matrix); 
        Matrix(Matrix<T> &&matrix) noexcept; //?

        Matrix(std::initializer_list<std::initializer_list<T>> list); 
        Matrix(T &fill_with, size_t rows, size_t columns); 
        Matrix(T **source, size_t rows, size_t columns); 

        void move(Matrix<T> &matrix);
        void move(Matrix<T> &&matrix);

        void move(const Matrix<T> &matrix);
        void move(const Matrix<T> &&matrix);

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

        bool operator ==(Matrix<T> &mat) const noexcept;
        bool operator != (Matrix<T> &mat) const noexcept;
        
        bool operator ==(const Matrix<T> &mat) const noexcept;
        bool operator != (const Matrix<T> &mat) const noexcept;


        Vector<T>& operator [](int pos); 
        const Vector<T>& operator [](int pos) const; 
        T& operator ()(int i, int j);

        T& get_elem(int i, int j);
        void set_elem(int i, int j, int num);

        void make_e_matrix();

        Iterator<T> begin() noexcept;
        Iterator<T> end() noexcept;

        constIterator<T> begin() const noexcept;
        constIterator<T> end() const noexcept;
        constIterator<T> cbegin() const noexcept;
        constIterator<T> cend() const noexcept;

        ~Matrix();

     private:
        std::shared_ptr<Vector[]> data;
        
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
        
        
        void reset() noexcept; 
        void reset(size_t size) noexcept; 
};

#include "matrix_checks.hpp"
#include "matrix_constructors_and_iter_methods.hpp"
#include "matrix_impl.hpp"
#include "exceptions.hpp"

#endif
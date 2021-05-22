#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <iostream>
#include <string>
#include "base_matrix_class.hpp"
#include "exceptions.hpp"

template <typename T>
class Vector;

template <typename T>
class Matrix : public BaseMatrix 
{        
    public:
        
        Matrix(size_t rows, size_t columns); 
        explicit Matrix(const Matrix<T> &matrix); 
        Matrix(Matrix<T> &&matrix) noexcept; 

        Matrix(std::initializer_list<std::initializer_list<T>> list); 
        Matrix(T &fill_with, size_t rows, size_t columns); 
        Matrix(T **source, size_t rows, size_t columns); 

        void move(Matrix<T> &&matrix);

        void copy(const Matrix<T> &matrix);

        Matrix<T>& operator =(const Matrix<T> &matrix);
        Matrix<T>& operator =(Matrix<T> &&matrix);

        Matrix<T>& operator =(std::initializer_list<std::initializer_list<T>> list);

        Matrix<T> add(const Matrix<T> &mat) const; 
        Matrix<T> operator +(const Matrix<T> &mat) const; 
    
        void addEq(const Matrix<T> &matrix);
        Matrix<T>& operator +=(const Matrix<T> &mat);

        Matrix<T> sub(const Matrix<T> &mat) const; 
        Matrix<T> operator -(const Matrix<T> &mat) const; 

        void subEq(const Matrix<T> &matrix);
        Matrix<T>& operator -=(const Matrix<T> &mat);

        Matrix<T> mul(const Matrix<T> &mat) const; 
        Matrix<T> operator *(const Matrix<T> &mat) const; 

        Matrix<T> mul(const T &elem) const;
        Matrix<T> operator *(const T &elem) const;
        
        void mulEq(const T &elem);
        Matrix<T>& operator *=(const T &elem); 

        bool operator ==(const Matrix<T> &mat) const noexcept;
        bool operator != (const Matrix<T> &mat) const noexcept;


        Vector<T>& operator [](int pos); 
        const Vector<T>& operator [](int pos) const; 

        void make_e_matrix();

        void make_move_matrix(Vector<T> &params);
        void make_scale_matrix(Vector<T> &params);
        void make_rotate_matrix(Vector<T> &params);

        Matrix<T> make_rotate_ox_matrix(T obj);
        Matrix<T> make_rotate_oy_matrix(T obj);
        Matrix<T> make_rotate_oz_matrix(T obj);
        
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
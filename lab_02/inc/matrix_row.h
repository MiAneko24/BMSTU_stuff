#ifndef MATRIX_ROW_H
#define MATRIX_ROW_H

#include <memory>
#include "matrix_templates.h"
#include "matrix_exceptions.h"
#define EPS 1e-8

template <typename T>
class Matrix;

template <typename T>
class MatrixRow 
{
    public:
        friend Matrix<T>;
        void reset();
        size_t getSize();
        void reset(T * new_array);
        void allocateMatrixRow(size_t size);
        MatrixRow(std::initializer_list<T> list, size_t columns);
        MatrixRow() : array(nullptr), rSize(0) {};
        MatrixRow(size_t size);
        MatrixRow(T *t_array, size_t t_size);
        MatrixRow(const MatrixRow<T> &matRow);
        T& operator[](size_t column) const; 
        MatrixRow<T> operator =(MatrixRow<T> &matRow);
        bool operator ==(MatrixRow<T> &matRow);

        bool operator !=(MatrixRow<T> &matRow);
        MatrixRow<T>& operator =(MatrixRow<T> &&matRow);
        ~MatrixRow(){};    
        
    private:
        void checkIndex(int pos) const;
        void checkList(std::initializer_list<T> list, size_t columns);
        void checkNull(T *array);
        std::shared_ptr<T[]> array = nullptr;
        size_t rSize = 0;
        void copy(const MatrixRow<T> &matRow);
        void move(MatrixRow<T> &matRow);
        void move(MatrixRow<T> &&matRow);
};

#include "matrix_row_methods.h"

#endif
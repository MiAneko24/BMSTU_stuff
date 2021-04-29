#ifndef CONST_ITERATOR_TEMPLATES_H
#define CONST_ITERATOR_TEMPLATES_H

#include <iterator>

#include "matrix_templates.h"
#include "iterator_exceptions.h"

template <typename T>
class Matrix;


template <typename T>
class constIterator : public std::iterator<std::input_iterator_tag, T> 
{
    public:
        constIterator(const Matrix<T> &matrix, const size_t index = 0)
            : iData(matrix.data), iIndex(index), iColumns(matrix.mColumns), iRows(matrix.mRows){};

        constIterator(const constIterator &iterator) = default;

        constIterator<T>& operator =(const constIterator<T> &iter);

        constIterator<T>& operator +(size_t add) const;
        constIterator<T>& operator +=(size_t add);

        constIterator<T>& operator ++();
        constIterator<T> operator ++(int);

        bool operator !=(constIterator const &iter) const;
        bool operator ==(constIterator const &iter) const;

        const T& operator *() const;

        const T* operator ->() const;

        operator bool() const;

        bool isEnd();

        bool isValid();

        constIterator<T>& next();

    private:
        std::weak_ptr<typename Matrix<T>::MatrixRow []> iData;
        size_t iIndex;
        size_t iRows;
        size_t iColumns;

        void checkIndex(std::string file, int line) const;
        void checkExpired(std::string file, int line) const;
};

#include "const_iterator_methods.h"

#endif
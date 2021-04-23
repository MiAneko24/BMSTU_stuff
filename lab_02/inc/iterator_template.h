#ifndef ITERATOR_TEMPLATE_H
#define ITERATOR_TEMPLATE_H

#include <iterator>

#include "matrix_templates.h"
#include "iterator_exceptions.h"

template <typename T>
class Iterator : public std::iterator<std::input_iterator_tag, T> 
{
    public:
        Iterator(const Matrix<T> &matrix, const size_t index = 0)
            : iData(matrix.data), iIndex(index), iColumns(matrix.getColumns()), iRows(matrix.getRows()){};

        Iterator(const Iterator &iterator) = default;

        bool operator !=(Iterator const &iter) const;
        bool operator ==(Iterator const &iter) const;

        Iterator<T>& operator =(const Iterator<T> &iter);

        Iterator<T>& operator ++();

        Iterator<T> operator ++(int);

        Iterator<T>& operator +(size_t add) const;

        Iterator<T>& operator +=(size_t add);

        const T& operator *() const;

        const T* operator ->() const;

        operator bool() const;

        bool isEnd();

        bool isValid();

        Iterator<T>& next();

    private:
        std::weak_ptr<MatrixRow<T> []> iData;
        size_t iIndex;
        size_t iRows;
        size_t iColumns;

        void checkIndex(std::string file, int line) const;
        void checkExpired(std::string file, int line) const;
};

#endif
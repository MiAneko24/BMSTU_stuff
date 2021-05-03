#ifndef BASE_MATRIX_CLASS_HPP
#define BASE_MATRIX_CLASS_HPP

#include <memory>
#include <iostream>

class BaseMatrix {
    public:
        explicit BaseMatrix(size_t rows, size_t columns) : mRows(rows), mColumns(columns) {};
        explicit BaseMatrix() : mRows(0), mColumns(0) {};
        virtual size_t getColumns() const noexcept
        {
            return mColumns;
        }
        virtual size_t getRows() const noexcept
        {
            return mRows;
        }
        virtual operator bool() const noexcept
        {
            return mRows && mColumns;
        }
        virtual ~BaseMatrix() = 0;
    protected:
        size_t mRows = 0;
        size_t mColumns = 0;
};

#endif
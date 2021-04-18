#include <memory>
#include <iostream>

class BaseMatrix {
    public:
        BaseMatrix(size_t rows, size_t columns) : mRows(rows), mColumns(columns) {};
        virtual size_t getColumns() const noexcept
        {
            return mRows;
        }
        virtual size_t getRows() const noexcept
        {
            return mColumns;
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

BaseMatrix :: ~BaseMatrix() {};
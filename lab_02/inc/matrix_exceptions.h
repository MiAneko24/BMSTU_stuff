#ifndef MATRIX_EXCEPTIONS_H
#define MATRIX_EXCEPTIONS_H

#include "base_exception.h"

class MemoryError : public BaseException
{
    public:
        MemoryError(std::string time, std::string file, std::string error_class, int line, std::string error_info)
        : BaseException(time, file, error_class, line, error_info){};
        const char* what() const noexcept
        {
            return error_msg.c_str();
        }
};

class IndexError : public BaseException
{
    public:
        IndexError(std::string time, std::string file, std::string error_class, int line, std::string error_info)
        : BaseException(time, file, error_class, line, error_info){};
        const char* what() const noexcept
        {
            return error_msg.c_str();
        }
};

class DivisionByZeroError : public BaseException
{
    public:
        DivisionByZeroError(std::string time, std::string file, std::string error_class, int line, std::string error_info)
        : BaseException(time, file, error_class, line, error_info){};
        const char* what() const noexcept
        {
            return error_msg.c_str();
        }
};

class NullPointerError : public BaseException
{
    public:
        NullPointerError(std::string time, std::string file, std::string error_class, int line, std::string error_info)
        : BaseException(time, file, error_class, line, error_info){};
        const char* what() const noexcept
        {
            return error_msg.c_str();
        }
};

class TypeMatrixError : public BaseException
{
    public:
        TypeMatrixError(std::string time, std::string file, std::string error_class, int line, std::string error_info)
        : BaseException(time, file, error_class, line, error_info){};
        const char* what() const noexcept
        {
            return error_msg.c_str();
        }
};


class DimensionMatrixError : public BaseException
{
    public:
        DimensionMatrixError(std::string time, std::string file, std::string error_class, int line, std::string error_info)
        : BaseException(time, file, error_class, line, error_info){};
        const char* what() const noexcept
        {
            return error_msg.c_str();
        }
};



#endif
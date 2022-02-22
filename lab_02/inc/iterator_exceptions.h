#ifndef ITERATOR_EXCEPTIONS_H
#define ITERATOR_EXCEPTIONS_H

#include "base_exception.h"

class IndexIteratorError : public BaseException
{
    public:
        IndexIteratorError(std::string time, std::string file, std::string error_class, int line, std::string error_info)
        : BaseException(time, file, error_class, line, error_info){};
        const char* what() const noexcept
        {
            return error_msg.c_str();
        }
};

class ExpiredError : public BaseException
{
    public:
        ExpiredError(std::string time, std::string file, std::string error_class, int line, std::string error_info)
        : BaseException(time, file, error_class, line, error_info){};
        const char* what() const noexcept
        {
            return error_msg.c_str();
        }
};

#endif
#ifndef ITERATOR_EXCEPTIONS_H
#define ITERATOR_EXCEPTIONS_H

#include <memory>
#include <iostream>

class BaseIteratorException : public std::exception
{
    public:
        BaseIteratorException(std::string time, std::string file, std::string error_class, int line, std::string error_info) 
        {
            error_msg = "Time: " + time + "\n In file " + file + ", class " + error_class + ", line " + std::to_string(line) + 
            "\n Error type: " + error_info + "\n";
        }

        virtual const char* what() const noexcept override
        {
            return error_msg.c_str();
        }
    protected:
        std::string error_msg;
};

class IndexIteratorError : public BaseIteratorException
{
    public:
        IndexIteratorError(std::string time, std::string file, std::string error_class, int line, std::string error_info)
        : BaseIteratorException(time, file, error_class, line, error_info){};
        const char* what() const noexcept
        {
            return error_msg.c_str();
        }
};

class ExpiredError : public BaseIteratorException
{
    public:
        ExpiredError(std::string time, std::string file, std::string error_class, int line, std::string error_info)
        : BaseIteratorException(time, file, error_class, line, error_info){};
        const char* what() const noexcept
        {
            return error_msg.c_str();
        }
};

#endif
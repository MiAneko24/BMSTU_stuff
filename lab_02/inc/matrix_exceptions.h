#include <memory>
#include <iostream>

class BaseMatrixException : public std::exception
{
    public:
        BaseMatrixException(std::string time, std::string file, std::string error_class, int line, std::string error_info) 
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

class MemoryError : public BaseMatrixException
{
    public:
        MemoryError(std::string time, std::string file, std::string error_class, int line, std::string error_info)
        : BaseMatrixException(time, file, error_class, line, error_info){};
        const char* what() const noexcept
        {
            return error_msg.c_str();
        }
};

class IndexError : public BaseMatrixException
{
    public:
        IndexError(std::string time, std::string file, std::string error_class, int line, std::string error_info)
        : BaseMatrixException(time, file, error_class, line, error_info){};
        const char* what() const noexcept
        {
            return error_msg.c_str();
        }
};

class NullPointerError : public BaseMatrixException
{
    public:
        NullPointerError(std::string time, std::string file, std::string error_class, int line, std::string error_info)
        : BaseMatrixException(time, file, error_class, line, error_info){};
        const char* what() const noexcept
        {
            return error_msg.c_str();
        }
};

class TypeMatrixError : public BaseMatrixException
{
    public:
        TypeMatrixError(std::string time, std::string file, std::string error_class, int line, std::string error_info)
        : BaseMatrixException(time, file, error_class, line, error_info){};
        const char* what() const noexcept
        {
            return error_msg.c_str();
        }
};


class DimensionMatrixError : public BaseMatrixException
{
    public:
        DimensionMatrixError(std::string time, std::string file, std::string error_class, int line, std::string error_info)
        : BaseMatrixException(time, file, error_class, line, error_info){};
        const char* what() const noexcept
        {
            return error_msg.c_str();
        }
};



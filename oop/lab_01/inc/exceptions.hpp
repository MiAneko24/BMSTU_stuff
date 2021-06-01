#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>

class BaseException : public std::exception
{
    public:
        BaseException(std::string time, std::string file, std::string error_class, int line, std::string error_info) 
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

class MemoryError : public BaseException
{
    public:
        MemoryError(std::string time, std::string file, std::string error_class, int line, std::string error_info = "Не удалось выделить память")
        : BaseException(time, file, error_class, line, error_info){};
        const char* what() const noexcept
        {
            return error_msg.c_str();
        }
};

class ExpiredError : public BaseException
{
    public:
        ExpiredError(std::string time, std::string file, std::string error_class, int line, std::string error_info = "Объекта, на который указывает итератор, не существует.")
        : BaseException(time, file, error_class, line, error_info){};
        const char* what() const noexcept
        {
            return error_msg.c_str();
        }
};


class IndexError : public BaseException
{
    public:
        IndexError(std::string time, std::string file, std::string error_class, int line, std::string error_info = "Некорректные данные: выход за границы массива")
        : BaseException(time, file, error_class, line, error_info){};
        const char* what() const noexcept
        {
            return error_msg.c_str();
        }
};

class DivisionByZeroError : public BaseException
{
    public:
        DivisionByZeroError(std::string time, std::string file, std::string error_class, int line, std::string error_info = "Деление на 0")
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
        TypeMatrixError(std::string time, std::string file, std::string error_class, int line, std::string error_info = "Тип матрицы не подходит для выполнения математических вычислений")
        : BaseException(time, file, error_class, line, error_info){};
        const char* what() const noexcept
        {
            return error_msg.c_str();
        }
};


class DimensionMatrixError : public BaseException
{
    public:
        DimensionMatrixError(std::string time, std::string file, std::string error_class, int line, std::string error_info = "Операнды (матрица и матрица, вектор и вектор, матрица и вектор) имеют несовместимые для операции размерности")
        : BaseException(time, file, error_class, line, error_info){};
        const char* what() const noexcept
        {
            return error_msg.c_str();
        }
};

class FileOpenError : public BaseException
{
    public:
        FileOpenError(std::string time, std::string file, std::string error_class, int line, std::string error_info = "Не удалось открыть файл")
        : BaseException(time, file, error_class, line, error_info){};
        const char* what() const noexcept
        {
            return error_msg.c_str();
        }
};


class FileDataError : public BaseException
{
    public:
        FileDataError(std::string time, std::string file, std::string error_class, int line, std::string error_info = "Некорректный формат входного файла")
        : BaseException(time, file, error_class, line, error_info){};
        const char* what() const noexcept
        {
            return error_msg.c_str();
        }
};


class DrawerError : public BaseException
{
    public:
        DrawerError(std::string time, std::string file, std::string error_class, int line, std::string error_info = "Отрисовщик не задан")
        : BaseException(time, file, error_class, line, error_info){};
        const char* what() const noexcept
        {
            return error_msg.c_str();
        }
};


class CameraError : public BaseException
{
    public:
        CameraError(std::string time, std::string file, std::string error_class, int line, std::string error_info = "Камера не установлена")
        : BaseException(time, file, error_class, line, error_info){};
        const char* what() const noexcept
        {
            return error_msg.c_str();
        }
};

class ObjectError : public BaseException
{
    public:
        ObjectError(std::string time, std::string file, std::string error_class, int line, std::string error_info = "Не удалось найти объект")
        : BaseException(time, file, error_class, line, error_info){};
        const char* what() const noexcept
        {
            return error_msg.c_str();
        }
};


#endif
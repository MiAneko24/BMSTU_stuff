#ifndef BASE_EXCEPTION_H
#define BASE_EXCEPTION_H
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

#endif
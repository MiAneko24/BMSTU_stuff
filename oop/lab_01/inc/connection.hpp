#ifndef CONNECTION_H
#define CONNECTION_H

#include <memory>

class Connection
{
    public:
        Connection() = default;
        Connection(const Connection &) = default;
        Connection(size_t el_1, size_t el_2);

        Connection& operator=(const Connection &) = default;

        size_t getFirst() const;
        size_t getSecond() const;

        void setFirst(size_t value);
        void setSecond(size_t value);
    
    private:
        size_t el_1;
        size_t el_2;
};

#endif
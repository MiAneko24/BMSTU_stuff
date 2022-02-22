#include "connection.hpp"

Connection::Connection(size_t elem_1, size_t elem_2) : el_1(elem_1), el_2(elem_2) {}

size_t Connection::getFirst() const
{
    return el_1;
}

size_t Connection::getSecond() const
{
    return el_2;
}

void Connection::setFirst(size_t value)
{
    el_1 = value;
}

void Connection::setSecond(size_t value)
{
    el_2 = value;
}
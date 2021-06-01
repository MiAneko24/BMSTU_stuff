#ifndef VECTORITERATOR_HPP
#define VECTORITERATOR_HPP

#include <iterator>
#include <memory>

template <typename T>
class Vector;

template <typename T>
class VectorIterator : public std::iterator<std::input_iterator_tag, T>
{
    public:
        VectorIterator(Vector<T> &vector, size_t index = 0) : iData(vector.array), iIndex(index), iAmount(vector.getSize()) {};

        VectorIterator() = default;
        
        VectorIterator<T>& operator =(VectorIterator<T> &iter);
        
        VectorIterator<T> operator +(size_t add);
        VectorIterator<T>& operator +=(size_t add);

        VectorIterator<T>& operator ++();
        VectorIterator<T> operator ++(int);
        
        bool operator !=(VectorIterator<T> &iter);
        bool operator ==(VectorIterator<T> &iter);

        T& operator *();

        T* operator ->();

        operator bool();

        bool isEnd();

        bool isValid();

        VectorIterator<T>& next();

    private:
        std::weak_ptr<T[]> iData;
        size_t iIndex;
        size_t iAmount;

        void checkIndex(std::string file, int line) const;
        void checkExpired(std::string file, int line) const;
};

#include "vector_iterator_methods.hpp"

#endif


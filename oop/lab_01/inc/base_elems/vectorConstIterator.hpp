#ifndef VECTORCONSTITERATOR_HPP
#define VECTORCONSTITERATOR_HPP

#include <iterator>

template <typename T>
class Vector;

template <typename T>
class VectorConstIterator : public std::iterator<std::input_iterator_tag, T>
{
    public:
        VectorConstIterator(const Vector<T> &vector, const size_t index = 0) : iData(vector.array), iIndex(index), iAmount(vector.getSize()) {};

        VectorConstIterator() = default;
        
        VectorConstIterator<T>& operator =(const VectorConstIterator<T> &iter);
        
        VectorConstIterator<T>& operator +(size_t add) const;
        VectorConstIterator<T>& operator +=(size_t add);

        VectorConstIterator<T>& operator ++();
        VectorConstIterator<T> operator ++(int);
        
        bool operator !=(VectorConstIterator const &iter) const;
        bool operator ==(VectorConstIterator const &iter) const;

        const T& operator *() const;

        const T* operator ->() const;

        operator bool() const;

        bool isEnd();

        bool isValid();

        VectorConstIterator<T>& next();

    private:
        std::weak_ptr<T[]> iData;
        size_t iIndex;
        size_t iAmount;

        void checkIndex(std::string file, int line) const;
        void checkExpired(std::string file, int line) const;
};

#include "vector_const_iterator_methods.hpp"
#endif


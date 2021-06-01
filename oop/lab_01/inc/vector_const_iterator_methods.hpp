#ifndef VECTOR_CONST_ITERATOR_METHODS_HPP
#define VECTOR_CONST_ITERATOR_METHODS_HPP
#include "vectorConstIterator.hpp"
#include "vector.hpp"
#include "exceptions.hpp"

template <typename T>
bool VectorConstIterator<T>::operator !=(VectorConstIterator const &iter) const 
{
    return iter.iIndex != iIndex;
}

template <typename T>
bool VectorConstIterator<T>::operator ==(VectorConstIterator const &iter) const
{
    return iter.iIndex == iIndex;
}

template <typename T>
VectorConstIterator<T>& VectorConstIterator<T>::operator =(const VectorConstIterator<T> &iter)
{
    iData = iter.iData;
    iIndex = iter.iIndex;
    iAmount = iter.iAmount;
}

template <typename T>
VectorConstIterator<T>& VectorConstIterator<T>::operator ++()
{
    if (iIndex < iAmount)
        ++iIndex;
    return *this;
}

template <typename T>
VectorConstIterator<T> VectorConstIterator<T>::operator ++(int)
{
    VectorConstIterator<T> tmp(*this);
    ++(*this);
    return tmp;
}

template <typename T>
VectorConstIterator<T>& VectorConstIterator<T>::operator +(size_t add) const
{
    VectorConstIterator<T> iter(*this);

    iter.iIndex += add;
    if (iter.iIndex > iter.iAmount)
        iter.iIndex = iter.iAmount;

    return iter;
}

template <typename T>
VectorConstIterator<T>& VectorConstIterator<T>::operator +=(size_t add)
{
    iIndex += add;
    if (iIndex > iAmount)
        iIndex = iAmount;

    return (*this);
}

template <typename T>
const T& VectorConstIterator<T>::operator *() const
{
    checkExpired(__FILE__, __LINE__);
    checkIndex(__FILE__, __LINE__);

    std::shared_ptr<T []> data = iData.lock();
    return data[iIndex];
}

template <typename T>
const T* VectorConstIterator<T>::operator ->() const 
{
    checkExpired(__FILE__, __LINE__);
    checkIndex(__FILE__, __LINE__);

    std::shared_ptr<T []> data = iData.lock();
    return data[iIndex];
}

template <typename T>
VectorConstIterator<T>::operator bool() const 
{
    return iData.expired();
}

template <typename T>
bool VectorConstIterator<T>::isEnd()
{
    return iIndex == iAmount;
}

template <typename T>
bool VectorConstIterator<T>::isValid()
{
    return !iData.expired();
}

template <typename T>
VectorConstIterator<T>& VectorConstIterator<T>::next()
{
    return operator++();
}

template <typename T>
void VectorConstIterator<T>::checkIndex(std::string file, int line) const
{
    if (iIndex > iAmount)
    {
        time_t time_cur = time(nullptr);
        throw IndexError(ctime(&time_cur), file, typeid(*this).name(), line, "VectorConstIterator out of bounds");
    }
}

template <typename T>
void VectorConstIterator<T>::checkExpired(std::string file, int line) const
{
    if (iData.expired())
    {
        time_t time_cur = time(nullptr);
        throw ExpiredError(ctime(&time_cur), file, typeid(*this).name(), line, "VectorConstIterator points on nullptr");
    }
}

#endif
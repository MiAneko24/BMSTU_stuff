#ifndef VECTOR_ITERATOR_METHODS_HPP
#define VECTOR_ITERATOR_METHODS_HPP
#include "vectorIterator.hpp"
#include "vector.hpp"
#include "exceptions.hpp"

template <typename T>
bool VectorIterator<T>::operator !=(VectorIterator &iter) 
{
    return iter.iIndex != iIndex;
}

template <typename T>
bool VectorIterator<T>::operator ==(VectorIterator &iter)
{
    return iter.iIndex == iIndex;
}

template <typename T>
VectorIterator<T>& VectorIterator<T>::operator =(VectorIterator<T> &iter)
{
    iData = iter.iData;
    iIndex = iter.iIndex;
    iAmount = iter.iAmount;
    return *this;
}

template <typename T>
VectorIterator<T>& VectorIterator<T>::operator ++()
{
    if (iIndex < iAmount)
        ++iIndex;
    return *this;
}

template <typename T>
VectorIterator<T> VectorIterator<T>::operator ++(int)
{
    VectorIterator<T> tmp = *this;
    ++(*this);
    return tmp;
}

template <typename T>
VectorIterator<T> VectorIterator<T>::operator +(size_t add)
{
    VectorIterator<T> iter(*this);

    iter.iIndex += add;
    if (iter.iIndex > iter.iAmount)
        iter.iIndex = iter.iAmount;

    return iter;
}

template <typename T>
VectorIterator<T>& VectorIterator<T>::operator +=(size_t add)
{
    iIndex += add;
    if (iIndex > iAmount)
        iIndex = iAmount;

    return (*this);
}

template <typename T>
T& VectorIterator<T>::operator *()
{
    checkExpired(__FILE__, __LINE__);
    checkIndex(__FILE__, __LINE__);

    std::shared_ptr<T []> data = iData.lock();
    return data[iIndex];
}

template <typename T>
T* VectorIterator<T>::operator ->()
{
    checkExpired(__FILE__, __LINE__);
    checkIndex(__FILE__, __LINE__);

    std::shared_ptr<T []> data = iData.lock();
    return data[iIndex];
}

template <typename T>
VectorIterator<T>::operator bool()
{
    return iData.expired();
}

template <typename T>
bool VectorIterator<T>::isEnd()
{
    return iIndex == iAmount;
}

template <typename T>
bool VectorIterator<T>::isValid()
{
    return !iData.expired();
}

template <typename T>
VectorIterator<T>& VectorIterator<T>::next()
{
    return operator++();
}

template <typename T>
void VectorIterator<T>::checkIndex(std::string file, int line) const
{
    if (iIndex > iAmount)
    {
        time_t time_cur = time(nullptr);
        throw IndexError(ctime(&time_cur), file, typeid(*this).name(), line, "VectorIterator out of bounds");
    }
}

template <typename T>
void VectorIterator<T>::checkExpired(std::string file, int line) const
{
    if (iData.expired())
    {
        time_t time_cur = time(nullptr);
        throw ExpiredError(ctime(&time_cur), file, typeid(*this).name(), line, "VectorIterator points on nullptr");
    }
}



#endif
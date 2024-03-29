#ifndef ITERATOR_METHODS_H
#define ITERATOR_METHODS_H

#include "iterator_template.h"

template <typename T>
bool Iterator<T>::operator !=(Iterator const &iter) const 
{
    return iter.iIndex != iIndex;
}

template <typename T>
bool Iterator<T>::operator ==(Iterator const &iter) const
{
    return iter.iIndex == iIndex;
}

template <typename T>
Iterator<T>& Iterator<T>::operator =(const Iterator<T> &iter)
{
    iData = iter.iData;
    iIndex = iter.iIndex;
    iRows = iter.iRows;
    iColumns = iter.iColumns;
}

template <typename T>
Iterator<T>& Iterator<T>::operator ++()
{
    if (iIndex < iRows * iColumns)
        ++iIndex;
    return *this;
}

template <typename T>
Iterator<T> Iterator<T>::operator ++(int)
{
    Iterator<T> tmp(*this);
    ++(*this);
    return tmp;
}

template <typename T>
Iterator<T>& Iterator<T>::operator +(size_t add) const
{
    Iterator<T> iter(*this);

    iter.iIndex += add;
    if (iter.iIndex > iter.iColumns * iter.iRows)
        iter.iIndex = iter.iColumns * iter.iRows;

    return iter;
}

template <typename T>
Iterator<T>& Iterator<T>::operator +=(size_t add)
{
    iIndex += add;
    if (iIndex > iColumns * iRows)
        iIndex = iColumns * iRows;

    return (*this);
}

template <typename T>
const T& Iterator<T>::operator *() const
{
    checkExpired(__FILE__, __LINE__);
    checkIndex(__FILE__, __LINE__);

    std::shared_ptr<typename Matrix<T>::MatrixRow []> matrix = iData.lock();
    return matrix[iIndex / iColumns][iIndex % iColumns];
}

template <typename T>
const T* Iterator<T>::operator ->() const 
{
    checkExpired(__FILE__, __LINE__);
    checkIndex(__FILE__, __LINE__);

    std::shared_ptr<typename Matrix<T>::MatrixRow []> matrix = iData.lock();
    return matrix[iIndex / iColumns][iIndex % iColumns];
}

template <typename T>
Iterator<T>::operator bool() const 
{
    return iData.expired();
}

template <typename T>
bool Iterator<T>::isEnd()
{
    return iIndex == iRows * iColumns;
}

template <typename T>
bool Iterator<T>::isValid()
{
    return !iData.expired();
}

template <typename T>
Iterator<T>& Iterator<T>::next()
{
    return operator++();
}

template <typename T>
void Iterator<T>::checkIndex(std::string file, int line) const
{
    if (iIndex > iRows * iColumns)
    {
        time_t time_cur = time(nullptr);
        throw IndexIteratorError(ctime(&time_cur), file, typeid(*this).name(), line, "Iterator out of bounds");
    }
}

template <typename T>
void Iterator<T>::checkExpired(std::string file, int line) const
{
    if (iData.expired())
    {
        time_t time_cur = time(nullptr);
        throw ExpiredError(ctime(&time_cur), file, typeid(*this).name(), line, "Iterator points on nullptr");
    }
}


#endif
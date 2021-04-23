#ifndef CONST_ITERATOR_METHODS_H
#define CONST_ITERATOR_METHODS_H

#include "const_iterator_templates.h"

template <typename T>
bool constIterator<T>::operator !=(constIterator const &iter) const 
{
    return iter.iIndex != iIndex;
}

template <typename T>
bool constIterator<T>::operator ==(constIterator const &iter) const
{
    return iter.iIndex == iIndex;
}

template <typename T>
constIterator<T>& constIterator<T>::operator =(const constIterator<T> &iter)
{
    iData = iter.iData;
    iIndex = iter.iIndex;
    iRows = iter.iRows;
    iColumns = iter.iColumns;
}

template <typename T>
constIterator<T>& constIterator<T>::operator ++()
{
    if (iIndex < iRows * iColumns)
        ++iIndex;
    return *this;
}

template <typename T>
constIterator<T> constIterator<T>::operator ++(int)
{
    constIterator<T> tmp(*this);
    ++(*this);
    return tmp;
}

template <typename T>
constIterator<T>& constIterator<T>::operator +(size_t add) const
{
    constIterator<T> iter(*this);

    iter.iIndex += add;
    if (iter.iIndex > iter.iColumns * iter.iRows)
        iter.iIndex = iter.iColumns * iter.iRows;

    return iter;
}

template <typename T>
constIterator<T>& constIterator<T>::operator +=(size_t add)
{
    iIndex += add;
    if (iIndex > iColumns * iRows)
        iIndex = iColumns * iRows;

    return (*this);
}

template <typename T>
const T& constIterator<T>::operator *() const
{
    checkExpired(__FILE__, __LINE__);
    checkIndex(__FILE__, __LINE__);

    std::shared_ptr<MatrixRow<T> []> matrix = iData.lock();
    return matrix[iIndex / iColumns][iIndex % iColumns];
}

template <typename T>
const T* constIterator<T>::operator ->() const 
{
    checkExpired(__FILE__, __LINE__);
    checkIndex(__FILE__, __LINE__);

    std::shared_ptr<MatrixRow<T> []> matrix = iData.lock();
    return matrix[iIndex / iColumns][iIndex % iColumns];
}

template <typename T>
constIterator<T>::operator bool() const 
{
    return iData.expired();
}

template <typename T>
bool constIterator<T>::isEnd()
{
    return iIndex == iRows * iColumns;
}

template <typename T>
bool constIterator<T>::isValid()
{
    return !iData.expired();
}

template <typename T>
constIterator<T>& constIterator<T>::next()
{
    return operator++();
}

template <typename T>
void constIterator<T>::checkIndex(std::string file, int line) const
{
    if (iIndex > iRows * iColumns)
    {
        time_t time_cur = time(nullptr);
        throw IndexIteratorError(ctime(&time_cur), file, typeid(*this).name(), line, "Iterator out of bounds");
    }
}

template <typename T>
void constIterator<T>::checkExpired(std::string file, int line) const
{
    if (iData.expired())
    {
        time_t time_cur = time(nullptr);
        throw ExpiredError(ctime(&time_cur), file, typeid(*this).name(), line, "Iterator points on nullptr");
    }
}

#endif
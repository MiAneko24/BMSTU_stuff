#pragma once
#include "matrix.hpp"

template <typename T>
class Vector 
{
    public:
        friend Matrix<T>;
        Vector() : array(nullptr), rSize(0) {};
        Vector(size_t size);
        Vector(const Vector<T> &vector);
        Vector(std::initializer_list<T> list, size_t columns);
        Vector(T *t_array, size_t t_size);

        void allocateVector(size_t size);

        void copy(Vector<T> &vector);
        
        void copy(const Vector<T> &vector);

        void move(Vector<T> &vector);
        void move(Vector<T> &&vector);
        
        void move(const Vector<T> &vector);
        void move(const Vector<T> &&vector);
        
        Vector operator =(Vector<T> &vector);
        Vector& operator =(Vector<T> &&vector);


        Vector operator =(const Vector<T> &vector);
        Vector& operator =(const Vector<T> &&vector);
        
        Vector operator *(Matrix<T> &matrix);

        bool operator ==(Vector<T> &vector) const noexcept;
        bool operator !=(Vector<T> &vector) const noexcept;

        bool operator ==(const Vector<T> &vector) const noexcept;
        bool operator !=(const Vector<T> &vector) const noexcept;

        T& operator[](size_t column) const; 

        size_t getSize() const noexcept;
        
        void reset() noexcept;
        
        ~Vector(){};   
        
    private:
        std::shared_ptr<T[]> array = nullptr;
        size_t rSize = 0;
        
        void checkIndex(int pos, std::string file, int line) const;
        void checkList(std::initializer_list<T> list, size_t columns, std::string file, int line);
        void checkNull(T *array, std::string file, int line);
        void checkSizes(Matrix<T> &matrix, std::string file, int line);
};

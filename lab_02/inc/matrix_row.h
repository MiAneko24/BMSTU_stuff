#include <iostream>
#include <memory>

template <typename T>
class MatrixRow 
{
    private:
        void checkIndex(size_t pos);
    protected:
        std::shared_ptr<T *> array = nullptr;
        size_t rSize = 0;

        void copy(MatrixRow<T> &matRow);
        
    public:
        friend Matrix;
        void reset();
        void reset(T * new_array);
        void allocateMatrixRow(size_t size);
        MatrixRow(std::initializer_list<T> list);
        MatrixRow() : array(nullptr), rSize(0) {};
        MatrixRow(T *t_array, size_t t_size) : array(t_array), rSize(t_size) {};
        explicit MatrixRow(const MatrixRow<T> &matRow);
        T& operator[](size_t column); 
        MatrixRow<T> operator =(MatrixRow<T> &matRow);
        ~MatrixRow();
        //void setNumber(size_t ind, size_t num);

    
};

template <typename T>
void MatrixRow<T>::reset()
{
    array.reset();
}

template <typename T>
void MatrixRow<T>::reset(T* new_arr)
{
    array.reset(new_arr);
}

template <typename T>
MatrixRow<T>::MatrixRow(std::initializer_list<T> list)
{
    int size = list.size();
    allocate_memory(size);
    size_t i = 0;
    for (T elem : list)
    {
        array[i] = elem;
        i++; 
    }
};

template <typename T>
void MatrixRow<T>::allocateMatrixRow(size_t size)
{
    rSize = size;
    array.reset(new T[size]);
}

template <typename T>
T& MatrixRow<T>::operator[](size_t column)
{
    return array[column];
}

template <typename T>
void MatrixRow<T>::copy(MatrixRow<T> &matRow)
{
    for (int i = 0; i < rSize; i++)
        array[i] = matRow.array[i];
}

template <typename T>
MatrixRow<T>::MatrixRow(const MatrixRow<T> &matRow)
{
    allocateMatrixRow(matRow.rSize);
    copy(matRow);
}

template <typename T>
MatrixRow<T> MatrixRow<T>::operator =(MatrixRow<T> &matRow)
{
    rSize = matRow.rSize;
    reset(matRow.array);
    return *this;
}
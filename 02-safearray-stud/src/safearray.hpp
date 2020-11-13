////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     Safearray class methods definition
/// \author    Sergey Shershakov
/// \version   0.2.0
/// \date      30.01.2017
///            This is a part of the course "Algorithms and Data Structures" 
///            provided by  the School of Software Engineering of the Faculty 
///            of Computer Science at the Higher School of Economics.
///
/// This file contains templates of the method of the class Safearray.
/// This file is not going to be used w/o its main counterpart, safearray.h.
/// Since the file is used only through safearray.h, which has its own "include 
/// watcher", we add no addition "watcher" here.
///
////////////////////////////////////////////////////////////////////////////////

// #ifndef    // No need to have a watcher here!


// we have to indicate that methods of the class Safearray are also inside the namespace xi
namespace xi {

template <typename T>
SafeArray<T>::SafeArray(size_t cap)
{
    _storage = new T[cap];
    _capacity = cap;
    // TODO: здесь необходимо добавить реализацию метода
}

// TODO: реализуйте остальные методы по образцу выше
template <typename T>
SafeArray<T>::~SafeArray()
{
     delete[] _storage;
     _storage = nullptr;
     _capacity = 0;
}

template <typename T>
size_t SafeArray<T>::getCapacity() const
{
    return _capacity;
}

template <typename T>
void SafeArray<T>::checkBounds(size_t index) const
{
    if(index >= _capacity)
    {
        throw std::out_of_range("Out of range!");
    }
}

template <typename T>
T& SafeArray<T>::operator[](size_t k)
{
    checkBounds(k);
    return _storage[k];
}

template <typename T>
const T& SafeArray<T>::operator[](size_t k) const
{
    checkBounds(k);
    return _storage[k];
}

template <typename T>
SafeArray<T>::SafeArray(const xi::SafeArray<T> &other)
{
    _storage = new T[other.getCapacity()];
    for (int i = 0; i < other.getCapacity(); ++i)
    {
        _storage[i] = other._storage[i];
    }
    _capacity = other.getCapacity();
}

template <typename T>
SafeArray<T>& SafeArray<T>::operator=(const xi::SafeArray<T> &other)
{
    _storage = new T[other.getCapacity()];
    for (int i = 0; i < other.getCapacity(); ++i)
    {
        _storage[i] = other._storage[i];
    }
    _capacity = other.getCapacity();
    return *this;
}

template <typename T>
const void SafeArray<T>::swap(xi::SafeArray<T>& safeArray_1, xi::SafeArray<T>& safeArray_2)
{
    T* swap_arr = safeArray_1._storage;
    safeArray_1._storage = safeArray_2._storage;
    safeArray_2._storage = swap_arr;
    size_t cap = safeArray_1.getCapacity();
    safeArray_1._capacity = safeArray_2._capacity;
    safeArray_2._storage = cap;
}
}// namespace xi

#include <string>
#include <stdexcept>
#include <utility>
#include <vector>
#include "NiceStack.h"
// TODO: implement all methods :)

template <class T>
NiceStack<T>::NiceStack(size_t capacity)
{
    _storage = std::vector<TypeElementStack>(capacity);
    _capacity = capacity;
    _iHead = 0;
}

template <class T>
void NiceStack<T>::push(const T& newelement)
{
    if(_iHead >= _capacity)
        throw std::out_of_range("Stack is FULL!!!");
    TypeElementStack elementStack (newelement, newelement);
    if(size() != 0)
    {
        T min = getMinimum();
        if(newelement < min)
            elementStack.second = newelement;
    }
    _storage[_iHead] = elementStack;
    _iHead++;
}

template <class T>
T NiceStack<T>::pop()
{
    if(size() == 0)
        throw std::out_of_range("Stack is EMPTY!!!");
    T elementStack = top();
    _iHead--;
    return elementStack;
}

template <class T>
const T& NiceStack<T>::top() const
{
    if(size() == 0)
        throw std::out_of_range("Stack is EMPTY!!!");
    return _storage[_iHead - 1].first;
}

template <class T>
size_t NiceStack<T>::size() const
{
    return _iHead;
}

template <class T>
const T& NiceStack<T>::getMinimum() const
{
    if(size() == 0)
        throw std::out_of_range("Stack is empty!");
    return _storage[_iHead - 1].second;
}

template <class T>
NiceStack<T>::~NiceStack()
{
    _capacity = 0;
    _iHead = 0;
}


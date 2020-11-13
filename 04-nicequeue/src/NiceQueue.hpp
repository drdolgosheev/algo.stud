#include <algorithm>
#include "NiceQueue.h"
#include <stdexcept>

// TODO: implenent all methods :)
template <class T>
NiceQueue<T>::NiceQueue(size_t capacity) : _inStack(capacity), _outStack(capacity)
{
    _capacity = capacity;
}

template <class T>
size_t NiceQueue<T>::size() const
{
    return _inStack.size() + _outStack.size();
}

template <class T>
void NiceQueue<T>::enq(const T &newElement)
{
    if(size() >= capacity())
        throw std::out_of_range("Queue is full!");
    _inStack.push(newElement);
}

template <class T>
T NiceQueue<T>::deq()
{
    if(size() == 0)
        throw std::out_of_range("Queue is empty");

    if(_outStack.size() !=0 )
        return _outStack.pop();

    while(_inStack.size() != 0)
    {
        _outStack.push(_inStack.pop());
    }


    return _outStack.pop();

}

template <class T>
T NiceQueue<T>::getMinimum()
{
    if(size() == 0)
        throw std::out_of_range("Queue is empty");

    T _tempMin;
    if (_inStack.size() != 0)
    {
        _tempMin = _inStack.getMinimum();
        if (_outStack.size() != 0)
            _tempMin = _tempMin < _outStack.getMinimum() ? _tempMin : _outStack.getMinimum();
    } else
        _tempMin = _outStack.getMinimum();

    return _tempMin;
}

template <class T>
NiceQueue<T>::~NiceQueue()
{
    _capacity = 0;
}
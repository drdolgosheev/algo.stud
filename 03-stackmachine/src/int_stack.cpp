////////////////////////////////////////////////////////////////////////////////
// Module Name:  int_stack.h/cpp
// Authors:      Sergey Shershakov
// Version:      0.2.0
// Date:         23.01.2017
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////


#include "int_stack.h"

// TODO: add necessary headers here
 #include <exception>
#include <stdexcept>


namespace xi {

// TODO: add method definitions here
    IntStack::IntStack(size_t sz)
    {
        _stack = new int[sz];
        _ssize = sz;
        _head = 0;
    }

    IntStack::~IntStack()
    {
        delete[] _stack;
        _head = 0;
        _ssize = 0;
    }

    int IntStack::pop()
    {
        if(isEmpty())
        {
            throw std::logic_error("Stack is empty!");
        }
        else
        {
            int _lastelement = _stack[_head - 1];
            _head -= 1;
            return _lastelement;
        }
    }

    void IntStack::push(int el)
    {
        if(isFull())
        {
            throw std::logic_error("Stack is full!");
        }
        else
        {
            _stack[_head] = el;
            _head += 1;
        }
    }

    int IntStack::top()
    {
        if(isEmpty())
            throw std::logic_error("Stack is empty!");
        return _stack[_head - 1];
    }

    bool IntStack::isEmpty() const
    {
        return _head == 0;
    }

    void IntStack::clear()
    {
        _head = 0;
    }

    bool IntStack::isFull() const
    {
        return _head == _ssize;
    }

} // namespace xi


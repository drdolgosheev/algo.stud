////////////////////////////////////////////////////////////////////////////////
// Module Name:  stack_machine.h/cpp
// Authors:      Sergey Shershakov
// Version:      0.2.0
// Date:         23.01.2017
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////

#include "stack_machine.h"

#include <vector>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <string>

namespace xi {

//==============================================================================
// Free functions -- helpers
//==============================================================================

// TODO: if you need any free functions, add their definitions here.

//==============================================================================
// class PlusOp
//==============================================================================


int PlusOp::operation(char op, int a, int b, int /*c*/) // < just commented unused argument. This does not affect the code anyhow.
{
    if(op != '+')
        throw std::logic_error("Operation other than Plus (+) are not supported");

    // here we just ignore unused operands
    return a + b;
}

IOperation::Arity PlusOp::getArity() const
{
    return arDue;
}


//==============================================================================
// class InverOp
//==============================================================================

int InverOp::operation(char op, int a, int b, int c)
{
    if(op != '~')
        throw std::logic_error("Operations other than Inversion (~) are not supported");

    return ~a;
}

IOperation::Arity InverOp::getArity() const
{
    return arUno;
}

//==============================================================================
// class AndOp
//==============================================================================

int AndOp::operation(char op, int a, int b, int c)
{
    if(op != '&')
        throw std::logic_error("Operations other than And (&) are not supported");
    return a&b;
}

IOperation::Arity AndOp::getArity() const
{
    return arDue;
}

//==============================================================================
// class OrOp
//==============================================================================

int OrOp::operation(char op, int a, int b, int c)
{
    if(op != '|')
        throw std::logic_error("Operations other than OR (|) are not supported");
    return a | b;
}

IOperation::Arity OrOp::getArity() const
{
    return arDue;
}

//==============================================================================
// class StackMachine
//==============================================================================


// TODO: put StackMachine methods implementation here
    void StackMachine::registerOperation(char symb, xi::IOperation *oper)
    {
        SymbolToOperMapConstIter it = _opers.find(symb);
        if(it != _opers.end())
            throw std::logic_error("An operation ... is alr. reg...");

        _opers[symb] = oper;
    }

    IOperation* StackMachine::getOperation(char symb)
    {
        if(_opers.find(symb) == _opers.end())
             return nullptr;
        return _opers.find(symb)->second;
    }

    int StackMachine::calculate(const std::string& expr, bool clearStack)
    {
        if(clearStack == true)
            _s.clear();
        std::vector<std::string> vector;
        std::string _str;
        for (int i = 0; i < expr.length(); ++i)
        {
            if(expr[i] != ' ')
                _str += expr[i];
            else
            {
                vector.push_back(_str);
                _str = "";
            }
        }

        vector.push_back(_str);

        for (auto line : vector)
        {
            IOperation* operation;
            int res = 0;
            if(line.length() == 1)
            {
                // mb operator
                operation = getOperation(line[0]);
                if(operation != nullptr)
                {
                    int arity = operation->getArity();
                    switch(arity)
                    {
                        case 0:
                            res = operation->operation(line[0], _s.pop());
                            _s.push(res);
                            break;
                        case 1:
                            res = operation->operation(line[0], _s.pop(), _s.pop());
                            _s.push(res);
                            break;
                        case 2:
                            res = operation->operation(line[0], _s.pop(), _s.pop(), _s.pop());
                            _s.push(res);
                            break;
                    }
                }
                else
                {
                    try
                    {
                        _s.push(std::stoi(line));
                    }
                    catch(std::exception& exc)
                    {
                        throw std::logic_error("Not a number");
                    }
                }
            }
            else
            {
                try
                {
                    _s.push(std::stoi(line));
                }
                catch(std::exception& exc)
                {
                    throw std::logic_error("Not a number");
                }
            }
        }

        return _s.top();
    }
} // namespace xi

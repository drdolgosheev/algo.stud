////////////////////////////////////////////////////////////////////////////////
// Module Name:  skip_list.h/hpp
// Authors:      Leonid Dworzanski, Sergey Shershakov
// Version:      2.0.0
// Date:         28.10.2018
//
// This is a part of the course "Algorithms and Data Structures"
// provided by  the School of Software Engineering of the Faculty
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////

// !!! DO NOT include skip_list.h here, 'cause it leads to circular refs. !!!

#include <cstdlib>
#include "exception"
#include "random"
//==============================================================================
// class NodeSkipList
//==============================================================================

template <class Value, class Key, int numLevels>
void NodeSkipList<Value, Key, numLevels>::clear(void)
{
    for (int i = 0; i < numLevels; ++i)
        Base::nextJump[i] = 0;

    Base::levelHighest = -1;
}

//------------------------------------------------------------------------------

template <class Value, class Key, int numLevels>
NodeSkipList<Value, Key, numLevels>::NodeSkipList(void)
{
    clear();
}

//------------------------------------------------------------------------------

template <class Value, class Key, int numLevels>
NodeSkipList<Value, Key, numLevels>::NodeSkipList(const Key& tkey)
{
    clear();

    Base::Base::key = tkey;
}

//------------------------------------------------------------------------------

template <class Value, class Key, int numLevels>
NodeSkipList<Value, Key, numLevels>::NodeSkipList(const Key& tkey, const Value& val)
{
    clear();

    Base::Base::key = tkey;
    Base::Base::value = val;
}


//==============================================================================
// class SkipList
//==============================================================================

template <class Value, class Key, int numLevels>
SkipList<Value, Key, numLevels>::SkipList(double probability)
{
    _probability = probability;

    // Lets use m_pPreHead as a final sentinel element
    for (int i = 0; i < numLevels; ++i)
        Base::_preHead->nextJump[i] = Base::_preHead;

    Base::_preHead->levelHighest = numLevels - 1;
}


    // TODO: !!! One need to implement all declared methods !!!

template <class Value, class Key, int numLevels>
SkipList<Value,Key,numLevels>::~SkipList()
{

}
    template <class Value, class Key, int numLevels>
    void SkipList<Value, Key,numLevels>::insert(const Value &val, const Key &key)
    {
        // Need to find element after which insert new elem
        Node* tmp = Base::_preHead;
        Node* arr[numLevels-1];
        for (int i = numLevels - 1; i > -1; --i)
        {
            while(tmp->nextJump[i] != Base::_preHead)
            {
                if(key >= tmp->nextJump[i]->key)
                {
                    tmp = tmp->nextJump[i];
                } else
                    break;
            }
            arr[i] = tmp;
        }
       // Now we need to add this element to 0 level and rand
        Node* newNode = new Node(key, val);
        Node* next = tmp->nextJump[0];
        Node* prev = tmp;

        prev->nextJump[0] = newNode;
        prev->next = newNode;
        newNode->nextJump[0] = next;
        newNode->next = next;
        newNode->levelHighest = 0;
        for (int i = 1; i < numLevels; ++i)
        {
            if(rand() % 100 > _probability * 100)
                break;
            newNode->nextJump[i] = arr[i]->nextJump[i];
            arr[i]->nextJump[i] = newNode;
            newNode->levelHighest = i;
        }
    }

template <class Value, class Key, int numLevels>
NodeSkipList<Value,Key, numLevels>* SkipList<Value, Key, numLevels>::findFirst(const Key &key) const
{
    Node* tmp = Base::_preHead;
    Node* move = tmp;
    for (int i = numLevels - 1; i > -1; --i)
    {
        while(move->nextJump[i] != Base::_preHead)
        {
            if(key < move->nextJump[i]->key)
            {
                break;
            }
            else if (key == move->nextJump[i]->key)
            {
                return move->nextJump[i];
            }
            else
            {
                move = move->nextJump[i];
            }
        }
    }
    if(move->key == key)
        tmp = move;
    else
    {
        if(move->next->key == key)
            tmp = move->next;
        else
            tmp = nullptr;
    }
    return tmp;
}

template <class Value, class Key, int numLevels>
NodeSkipList<Value,Key, numLevels>* SkipList<Value,Key, numLevels>::findLastLessThan(const Key &key) const
{
    Node* tmp = Base::_preHead;
    Node* move = tmp;
    for (int i = numLevels - 1; i > -1; --i)
    {
        while(move->nextJump[i] != Base::_preHead)
        {
            if(key < move->nextJump[i]->key)
            {
                break;
            }
            else if (key == move->nextJump[i]->key)
            {
                return move;
            }
            else
            {
                move = move->nextJump[i];
            }
        }
    }
    if(move->key == key)
        tmp = move;
    else
    {
        if(move->next->key == key)
            tmp = move;
        else
            tmp = nullptr;
    }
    return tmp;
}

template <class Value, class Key, int numLevels>
void SkipList<Value,Key,numLevels>::removeNext(SkipList<Value, Key, numLevels>::Node *nodeBefore)
{
    if(!nodeBefore || nodeBefore->next == Base::_preHead)
        throw std::invalid_argument("Invalid argument");
    Node* tmp = Base::_preHead;
    Node* toDel = nodeBefore->next;
    Node* arr[toDel->levelHighest];
    for (int i = toDel->levelHighest; i > -1; --i)
    {
        while(tmp->nextJump[i] != Base::_preHead)
        {
            if(tmp->nextJump[i]->key < toDel->key)
            {
                tmp = tmp->nextJump[i];
            } else
            {
                arr[i] = tmp;
                break;
            }
        }
    }
    for (int i = toDel->levelHighest; i > -1; --i)
    {
        arr[i]->nextJump[i] = toDel->nextJump[i];
    }
    nodeBefore->next = toDel->next;
    delete toDel;
}

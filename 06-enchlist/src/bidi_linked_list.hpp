///////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Contains pseudo-implementation part of bidirectional list structure 
/// template declared in the file's h-counterpart
///
/// © Sergey Shershakov 2015–2017.
///
/// This code is for educational purposes of the course "Algorithms and Data 
/// Structures" provided by the School of Software Engineering of the Faculty 
/// of Computer Science at the Higher School of Economics.
///
/// When altering code, a copyright line must be preserved.
///////////////////////////////////////////////////////////////////////////////

#include <stdexcept>

//==============================================================================
// class BidiList<T>::Node
//==============================================================================


template <typename T>
typename BidiLinkedList<T>::Node* 
    BidiLinkedList<T>::Node::insertAfterInternal(Node* insNode)
{
    // here we use "this" keyword for enhancing the fact we deal with curent node!
    Node* afterNode = this->_next;      // an element, which was after node
    this->_next = insNode;
    insNode->_next = afterNode;
    insNode->_prev = this;
    // !...
    // Здесь вырезана часть кода. Ее необходимо реализовать
    // См. документацию к методу insertAfterInternal() и insertAfter()
    // !...
    if(afterNode != nullptr)
        afterNode->_prev = insNode;
    return insNode;
}

//==============================================================================
// class BidiList<T>
//==============================================================================



template <typename T>
BidiLinkedList<T>::~BidiLinkedList()
{
    clear();
}

template <typename T>
BidiLinkedList<T>::BidiLinkedList(const BidiLinkedList& other)
{
    Node* prev;
    Node* listHead = other._head;
    _head = new Node();
    Node* newNext = _head;
    while(listHead->_next)
    {
        if(listHead == other._head)
            _head->setValue(other._head->getValue());
        listHead = listHead->_next;
        newNext->_next = new Node();
        prev = newNext;
        newNext = newNext->_next;
        newNext->setValue(listHead->getValue());
        newNext->_prev = prev;
        _tail = newNext;
    }
    _size = other._size;
}

template <typename T>
void BidiLinkedList<T>::swap(BidiLinkedList& left, BidiLinkedList& right)
{
    Node* leftHead = left._head;
    Node* leftTail = left._tail;
    size_t leftSize = left._size;

    left._tail = right._tail;
    left._head = right._head;
    left._size = right._size;

    right._head = leftHead;
    right._tail = leftTail;
    right._size = leftSize;
}

template <typename T>
BidiLinkedList<T>& BidiLinkedList<T>::operator=(const BidiLinkedList& other)
{
    BidiLinkedList<T> cur(other);
    swap(*this, cur);
    return *this;
}

template <typename T>
void BidiLinkedList<T>::clear()
{
    // !...
    // Метод необходимо реализовать целиком!
    // !...
    Node* cur = _head;
    while(cur != nullptr)
    {
        Node* toDel = cur;
        cur = cur->_next;
        delete toDel;
    }
}

template <typename T>
size_t BidiLinkedList<T>::getSize()
{
    if (_size == NO_SIZE)
        calculateSize();

    return _size;
}


template <typename T>
void BidiLinkedList<T>::calculateSize()
{
    // !...
    // Метод необходимо реализовать целиком!
    // !...
    size_t count = 0;
    Node* _preHead = getHeadNode();
    while(_preHead != nullptr)
    {
        _preHead = _preHead->_next;
        count++;
    }
    _size = count;
}


template <typename T>
typename BidiLinkedList<T>::Node* 
    BidiLinkedList<T>::getLastNode() const
{
    // !...
    // Метод необходимо реализовать целиком!
    // !...
    return _tail;
}


template <typename T>
typename BidiLinkedList<T>::Node* 
    BidiLinkedList<T>::appendEl(const T& val)
{
    Node* newNode = new Node(val);

    // !...
    // Здесь вырезана часть кода. Ее необходимо реализовать
    // !...

    // inserts after last node, size if going to e invalidated there
    return insertNodeAfter(getLastNode(), newNode);
}


// возможно, этот метод даже не надо изменять
template <typename T>
typename BidiLinkedList<T>::Node* 
    BidiLinkedList<T>::insertNodeAfter(Node* node, Node* insNode)
{
    if (!insNode)
        throw std::invalid_argument("`insNode` is nullptr");

    // check if a node is alone
    if (insNode->_next || insNode->_prev)
        throw std::invalid_argument("`insNode` has siblings. It seems it isn't free");


    if (!node)
        node = getLastNode();

    // if last node is nullptr itself, it means that no elements in the list at all
    if (!node)
    {
        _head = insNode;
        _tail = insNode;
    }
    else
    {
        node->insertAfterInternal(insNode);
        // If there is no one on the right from the inserted, update _tail.
        if (!insNode->_next)
            _tail = insNode;
    }

    invalidateSize();

    return insNode;
}

template <typename T>
void BidiLinkedList<T>::insertNodesAfter(BidiLinkedList<T>::Node *node, BidiLinkedList<T>::Node *beg,
                                         BidiLinkedList<T>::Node *end)
{
    if(!beg || !end)
        throw std::invalid_argument("Invalid arg");
    if(beg->_prev || end->_next)
        throw std::invalid_argument("inv arg");

    if(!node)
    {
        if(!_head) // empty list
        {
            _head = beg;
            _tail = end;
        } else
        {
            Node* cur = _tail;
            cur->_next = beg;
            beg->_prev = cur;
            _tail = end;
        }
        invalidateSize();
        return;
    }
    Node* afterNode = node->_next;
    node->_next = beg;
    beg->_prev = node;
    if(!afterNode)
    {
        end->_next = nullptr;
        _tail = end;
    }
    else
    {
        end->_next = afterNode;
        afterNode->_prev = end;
    }
    invalidateSize();
}



// !...
// Здесь должна быть реализация метода BidiLinkedList<T>::insertNodesAfter().
// В отличие от других методов, здесь не представлен даже заголовок, поэтому придется потрудиться!
// !...


// Следующий фрагмент кода перестанет быть "блеклым" и станет "ярким", как только вы определите
// макрос IWANNAGET10POINTS, взяв тем самым на себя повышенные обязательства
#ifdef IWANNAGET10POINTS


template <typename T>
typename BidiLinkedList<T>::Node*
    BidiLinkedList<T>::insertNodeBefore(Node* node, Node* insNode)
{
    // !...
    // Реализуй метод, если хочешь получит оценку повыше!
    // !...

    if(!insNode)
        throw std::invalid_argument("insNode - null");
    if(insNode->_next || insNode->_prev)
        throw std::invalid_argument("invalid arg");

    if(!node) // node is nullptr
    {
        Node* _cur = _head;
        _head = insNode;
        insNode->_next = _cur;
        // if list was empty
        if(!_cur)
            _tail = insNode;
        else
            _cur->_prev = insNode;
        invalidateSize();
        return insNode;
    }

    Node* prev = node->_prev;
    insNode->_next = node;
    insNode->_prev = prev;
    node->_prev = insNode;
    if(!prev) // if node's left is empty
        _head = insNode;
    else
        prev->_next = insNode;

    invalidateSize();
    return insNode;
}


template <typename T>
void BidiLinkedList<T>::insertNodesBefore(Node* node, Node* beg, Node* end)
{
    // !...
    // Реализуй метод, если хочешь получит оценку повыше!
    // !...
    if(!beg || !end)
        throw std::invalid_argument("inv arg");
    if(beg->_prev || end->_next)
        throw std::invalid_argument("inv arg");

    if(!node)
    {
        if(!_head)
        {
            _head = beg;
            _tail = end;
            invalidateSize();
            return;
        }
        Node* next = _head;
        end->_next = next;
        _head = beg;
        next->_prev = end;
        invalidateSize();
        return;
    }

    Node* beforeNode = node->_prev;
    node->_prev = end;
    end->_next = node;
    if(!beforeNode)
    {
        beg->_prev = nullptr;
        end->_next = _head;
        _head = beg;
    }
    else
    {
        beg->_prev = beforeNode;
        beforeNode->_next = beg;
    }
    invalidateSize();

}

#endif // IWANNAGET10POINTS


template <typename T>
void BidiLinkedList<T>::cutNodes(Node* beg, Node* end)
{
    if (!beg || !end)
        throw std::invalid_argument("Either `beg` or `end` is nullptr");
    // !...
    // Здесь вырезана часть кода. Ее необходимо реализовать
    // !...
    Node* prev = beg->_prev;
    Node* next = end->_next;

    if(!prev) // trying to delete from head
    {
        _head = next;
        if(_head)
            _head->_prev = nullptr;
    } else
    {
        prev->_next = next;
    }

    if(!next) // trying to delete from smth to _tail
    {
        _tail = prev;
        if(_tail)
            _tail->_next = nullptr;
    } else
        next->_prev = prev;

    beg->_prev = nullptr;
    end->_next = nullptr;

    invalidateSize();

}


template <typename T>
typename BidiLinkedList<T>::Node* 
    BidiLinkedList<T>::cutNode(Node* node)
{
    // !...
    // Метод необходимо реализовать целиком!
    // !...
    if(!node)
        throw std::invalid_argument("Node is null");
    if((!node->_next && node != _tail) || (!node->_prev && node != _head))
        throw std::invalid_argument("Not a part of list");
    // first last or nor of this check
    if(node->_prev && node->_next)
    {
        Node* _previous = node->_prev;
        Node* _after = node->_next;
        _previous->_next = _after;
        _after->_prev = _previous;
    }
    else if (node->_next)
    {
        _head = node->_next;
        _head->_prev = nullptr;
    }
    else if(node->_prev)
    {
        _tail = node->_prev;
        _tail->_next = nullptr;
    } else
    {
        _head = nullptr;
        _tail = nullptr;
    }
    // cut node
    node->_next = nullptr;
    node->_prev = nullptr;
    invalidateSize(); // size was changed
    return node;
}


template <typename T>
typename BidiLinkedList<T>::Node* 
    BidiLinkedList<T>::findFirst(Node* startFrom, const T& val)
{
    if (!startFrom)
        return nullptr;

    // !...
    // Здесь вырезана часть кода. Ее необходимо реализовать
    // !...
    Node* forward = startFrom;
    Node* backwards = startFrom;
    if(startFrom->_next && startFrom->_prev)
    {
        while (forward || backwards)
        {
            if (forward)
            {
                if(forward->_val == val)
                    return forward;
                forward = forward->_next;
            }

            else if (backwards)
            {
                if(backwards->_val == val)
                    return backwards;
                backwards = backwards->_prev;
            }
        }
        return nullptr; //not found
    } else if (startFrom->_next)
    {
        while(forward)
        {
            if (forward->_val == val)
                return forward;
            forward = forward->_next;
        }
        return nullptr; // not found
    } else if(startFrom ->_prev)
    {
        while(backwards)
        {
            if(backwards->_val == val)
                return backwards;
            backwards = backwards->_prev;
        }
        return nullptr; // not found
    }

    return nullptr;     // not a part of list
}



template <typename T>
typename BidiLinkedList<T>::Node**
    BidiLinkedList<T>::findAll(Node* startFrom, const T& val, int& size)
{
    if (!startFrom)
        return nullptr;

    // try not to use any standard containers. create an array only when found a first occurence  
    Node** res = nullptr;
    size = 0;
    Node* cur = startFrom;
    int i = 0;
    while (cur)
    {
        // !...
        // Здесь вырезана часть кода. Ее необходимо реализовать
        // !...
        if(cur->_val == val)
        {
            size++;
        }
        cur = cur->_next;
    }

    if(size == 0)
        return nullptr;
    else
        res = new Node*[size];

    cur = startFrom;
    while(cur)
    {
        if(cur->_val == val)
            res[i++] = cur;
        cur = cur->_next;
    }

    return res;
}

template <typename T>
typename BidiLinkedList<T>::iterator
    BidiLinkedList<T>::begin()
{
    if(!_head)
        throw std::logic_error("list is empty");
    return iterator(_head, *this);
}

template <typename T>
typename BidiLinkedList<T>::iterator
BidiLinkedList<T>::end()
{
    if(!_head)
        throw std::logic_error("list is empty");
    return iterator(_tail->_next, *this);
}

template <typename T>
typename BidiLinkedList<T>::reverse_iterator
BidiLinkedList<T>::rbegin()
{
    if(!_head)
        throw std::logic_error("list is empty");
    return reverse_iterator(_tail, *this);
}

template <typename T>
typename BidiLinkedList<T>::reverse_iterator
BidiLinkedList<T>::rend()
{
    if(!_head)
        throw std::logic_error("list is empty");
    return reverse_iterator(_head->_prev, *this);
}


template <typename T>
typename BidiLinkedList<T>::const_iterator
BidiLinkedList<T>::cbegin()
{
    if(!_head)
        throw std::logic_error("list is empty");
    return const_iterator(_head, *this);
}

template<typename T>
typename BidiLinkedList<T>::const_iterator
BidiLinkedList<T>::cend()
{
    if(!_head)
        throw std::logic_error("list is empty");
    return const_iterator(_tail->_next, *this);
}

template<typename T>
typename BidiLinkedList<T>::const_reverse_iterator
BidiLinkedList<T>::crend()
{
    if(!_head)
        throw std::logic_error("list is empty");
    return const_reverse_iterator(_head->_prev, *this);
}

template<typename T>
typename BidiLinkedList<T>::const_reverse_iterator
BidiLinkedList<T>::crbegin()
{
    if(!_head)
        throw std::logic_error("list is empty");
    return const_reverse_iterator(_tail, *this);
}

//==============================================================================
// class MyIterator
//==============================================================================

template <typename T>
typename BidiLinkedList<T>::MyIterator&
BidiLinkedList<T>::MyIterator::operator=(const BidiLinkedList<T>::MyIterator& it)
{
    this->_curNode = it._curNode;
    return *this;
}

template <typename T>
typename BidiLinkedList<T>::MyIterator&
BidiLinkedList<T>::MyIterator::operator++()
{
    if(!_curNode)
        throw std::logic_error("error");
    _curNode = _curNode->_next;
    return *this;
}

template <typename T>
typename BidiLinkedList<T>::MyIterator
BidiLinkedList<T>::MyIterator::operator++(int)
{
    if(!_curNode)
        throw std::logic_error("error");
    MyIterator cur = *this;
    _curNode = _curNode->_next;
    return cur;
}

template <typename T>
typename BidiLinkedList<T>::MyIterator
BidiLinkedList<T>::MyIterator::operator--(int)
{
    MyIterator cur = *this;
    _curNode = _curNode -> _prev;
    return cur;
}

template <typename T>
typename BidiLinkedList<T>::MyIterator&
BidiLinkedList<T>::MyIterator::operator--()
{
    if(!_curNode)
        _curNode = _lst.getLastNode();
    else
        _curNode = _curNode -> _prev;
    return *this;
}

template <typename T>
bool BidiLinkedList<T>::MyIterator::operator!=(const BidiLinkedList<T>::MyIterator &it) const
{
    return _curNode != it._curNode;
}

template <typename T>
bool BidiLinkedList<T>::MyIterator::operator==(const BidiLinkedList<T>::MyIterator &it) const
{
    return _curNode == it._curNode;
}

template <typename T>
T& BidiLinkedList<T>::MyIterator::operator*()
{
    return _curNode->_val;
}

template <typename T>
T*
BidiLinkedList<T>::MyIterator::operator->()
{
    T* value = &(_curNode->_val);
    return value;
}

//==============================================================================
// class Const_MyIterator
//==============================================================================


template <typename T>
typename BidiLinkedList<T>::Const_MyIterator&
BidiLinkedList<T>::Const_MyIterator::operator=(const BidiLinkedList<T>::Const_MyIterator& it)
{
    this->_curNode = it._curNode;
    return *this;
}

template <typename T>
typename BidiLinkedList<T>::Const_MyIterator&
BidiLinkedList<T>::Const_MyIterator::operator++()
{
    if(!_curNode)
        throw std::logic_error("error");
    _curNode = _curNode->_next;
    return *this;
}

template <typename T>
typename BidiLinkedList<T>::Const_MyIterator
BidiLinkedList<T>::Const_MyIterator::operator++(int)
{
    if(!_curNode)
        throw std::logic_error("error");
    Const_MyIterator it = *this;
    _curNode = _curNode->_next;
    return it;
}

template <typename T>
typename BidiLinkedList<T>::Const_MyIterator
BidiLinkedList<T>::Const_MyIterator::operator--(int)
{
    Const_MyIterator it = *this;
    _curNode = _curNode->_prev;
    return it;
}

template <typename T>
typename BidiLinkedList<T>::Const_MyIterator&
BidiLinkedList<T>::Const_MyIterator::operator--()
{
    if(!_curNode)
        _curNode = _lst.getLastNode();
    else
        _curNode = _curNode -> _prev;
    return *this;
}

template <typename T>
bool BidiLinkedList<T>::Const_MyIterator::operator!=(const BidiLinkedList<T>::Const_MyIterator &it) const
{
    return _curNode != it._curNode;
}

template <typename T>
bool BidiLinkedList<T>::Const_MyIterator::operator==(const BidiLinkedList<T>::Const_MyIterator &it) const
{
    return _curNode == it._curNode;
}

template <typename T>
const T& BidiLinkedList<T>::Const_MyIterator::operator*() const
{
    return _curNode->_val;
}

template <typename T>
T*
BidiLinkedList<T>::Const_MyIterator::operator->() const
{
    return &_curNode->_val;
}

//==============================================================================
// class Reverse_MyIterator
//==============================================================================

template <typename T>
typename BidiLinkedList<T>::Reverse_MyIterator&
BidiLinkedList<T>::Reverse_MyIterator::operator=(const BidiLinkedList<T>::Reverse_MyIterator& it)
{
    this->_curNode = it._curNode;
    return *this;
}

template <typename T>
typename BidiLinkedList<T>::Reverse_MyIterator&
BidiLinkedList<T>::Reverse_MyIterator::operator++()
{
    if(!_curNode)
        _curNode = _lst.getLastNode();
    else
        _curNode = _curNode -> _prev;
    return *this;
}

template <typename T>
typename BidiLinkedList<T>::Reverse_MyIterator
BidiLinkedList<T>::Reverse_MyIterator::operator++(int)
{
    if(!_curNode)
        throw std::logic_error("error");
    Reverse_MyIterator cur = *this;
    _curNode = _curNode->_prev;
    return cur;
}

template <typename T>
typename BidiLinkedList<T>::Reverse_MyIterator
BidiLinkedList<T>::Reverse_MyIterator::operator--(int)
{
    if(!_curNode)
        throw std::logic_error("error");
    Reverse_MyIterator cur = *this;
    _curNode = _curNode->_next;
    return cur;
}

template <typename T>
typename BidiLinkedList<T>::Reverse_MyIterator&
BidiLinkedList<T>::Reverse_MyIterator::operator--()
{
    if(!_curNode)
        throw std::logic_error("error");
    _curNode = _curNode->_next;
    return *this;
}

template <typename T>
bool BidiLinkedList<T>::Reverse_MyIterator::operator!=(const BidiLinkedList<T>::Reverse_MyIterator &it) const
{
    return _curNode != it._curNode;
}

template <typename T>
bool BidiLinkedList<T>::Reverse_MyIterator::operator==(const BidiLinkedList<T>::Reverse_MyIterator &it) const
{
    return _curNode == it._curNode;
}

template <typename T>
T& BidiLinkedList<T>::Reverse_MyIterator::operator*()
{
    return _curNode->_val;
}

template <typename T>
T*
 BidiLinkedList<T>::Reverse_MyIterator::operator->()
{
    return &_curNode->_val;
}

//==============================================================================
// class Const_Reverse_MyIterator
//==============================================================================


template <typename T>
typename BidiLinkedList<T>::Const_Reverse_MyIterator&
BidiLinkedList<T>::Const_Reverse_MyIterator::operator=(const BidiLinkedList<T>::Const_Reverse_MyIterator& it)
{
    this->_curNode = it._curNode;
    return *this;
}

template <typename T>
typename BidiLinkedList<T>::Const_Reverse_MyIterator&
BidiLinkedList<T>::Const_Reverse_MyIterator::operator++()
{
    if(!_curNode)
        _curNode = _lst.getLastNode();
    else
        _curNode = _curNode -> _prev;
    return *this;
}

template <typename T>
typename BidiLinkedList<T>::Const_Reverse_MyIterator
BidiLinkedList<T>::Const_Reverse_MyIterator::operator++(int)
{
    if(!_curNode)
        throw std::logic_error("error");
    Const_Reverse_MyIterator cur = *this;
    _curNode = _curNode->_prev;
    return cur;
}

template <typename T>
typename BidiLinkedList<T>::Const_Reverse_MyIterator
BidiLinkedList<T>::Const_Reverse_MyIterator::operator--(int)
{
    Const_Reverse_MyIterator cur = *this;
    _curNode = _curNode->_next;
    return cur;
}

template <typename T>
typename BidiLinkedList<T>::Const_Reverse_MyIterator&
BidiLinkedList<T>::Const_Reverse_MyIterator::operator--()
{
    _curNode = _curNode->_next;
    return *this;
}

template <typename T>
bool BidiLinkedList<T>::Const_Reverse_MyIterator::operator!=(const BidiLinkedList<T>::Const_Reverse_MyIterator &it) const
{
    return _curNode != it._curNode;
}

template <typename T>
bool BidiLinkedList<T>::Const_Reverse_MyIterator::operator==(const BidiLinkedList<T>::Const_Reverse_MyIterator &it) const
{
    return _curNode == it._curNode;
}

template <typename T>
const T& BidiLinkedList<T>::Const_Reverse_MyIterator::operator*() const
{
    return _curNode->_val;
}

template <typename T>
 T*
 BidiLinkedList<T>::Const_Reverse_MyIterator::operator->() const
{
    return &_curNode->_val;
}
// Следующий фрагмент кода перестанет быть "блеклым" и станет "ярким", как только вы определите
// макрос IWANNAGET10POINTS, взяв тем самым на себя повышенные обязательства
#ifdef IWANNAGET10POINTS

template <typename T>
typename BidiLinkedList<T>::Node**  
BidiLinkedList<T>::cutAll(Node* startFrom, const T& val, int& size)
{
    // !...
    // Реализуй метод, если хочешь получит оценку повыше!
    // !...
    Node** toCut = findAll(startFrom, val, size);
    int i = 0;
    while(i < size)
    {
        cutNode(toCut[i]);
        i++;
    }
    return toCut;
}

#endif // IWANNAGET10POINTS

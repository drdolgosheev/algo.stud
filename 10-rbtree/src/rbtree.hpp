////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief     Реализация классов красно-черного дерева
/// \author    Sergey Shershakov
/// \version   0.1.0
/// \date      01.05.2017
///            This is a part of the course "Algorithms and Data Structures" 
///            provided by  the School of Software Engineering of the Faculty 
///            of Computer Science at the Higher School of Economics.
///
/// "Реализация" (шаблонов) методов, описанных в файле rbtree.h
///
////////////////////////////////////////////////////////////////////////////////

#include <stdexcept>        // std::invalid_argument


namespace xi {


//==============================================================================
// class RBTree::node
//==============================================================================

template <typename Element, typename Compar >
RBTree<Element, Compar>::Node::~Node()
{
    if (_left)
        delete _left;
    if (_right)
        delete _right;
}



template <typename Element, typename Compar>
typename RBTree<Element, Compar>::Node* RBTree<Element, Compar>::Node::setLeft(Node* lf)
{
    // предупреждаем повторное присвоение
    if (_left == lf)
        return nullptr;

    // если новый левый — действительный элемент
    if (lf)
    {
        // если у него был родитель
        if (lf->_parent)
        {
            // ищем у родителя, кем был этот элемент, и вместо него ставим бублик
            if (lf->_parent->_left == lf)
                lf->_parent->_left = nullptr;
            else                                    // доп. не проверяем, что он был правым, иначе нарушение целостности
                lf->_parent->_right = nullptr;      
        }

        // задаем нового родителя
        lf->_parent = this;
    }

    // если у текущего уже был один левый — отменяем его родительскую связь и вернем его
    Node* prevLeft = _left;
    _left = lf;

    if (prevLeft)
        prevLeft->_parent = nullptr;

    return prevLeft;
}


template <typename Element, typename Compar>
typename RBTree<Element, Compar>::Node* RBTree<Element, Compar>::Node::setRight(Node* rg)
{
    // предупреждаем повторное присвоение
    if (_right == rg)
        return nullptr;

    // если новый правый — действительный элемент
    if (rg)
    {
        // если у него был родитель
        if (rg->_parent)
        {
            // ищем у родителя, кем был этот элемент, и вместо него ставим бублик
            if (rg->_parent->_left == rg)
                rg->_parent->_left = nullptr;
            else                                    // доп. не проверяем, что он был правым, иначе нарушение целостности
                rg->_parent->_right = nullptr;
        }

        // задаем нового родителя
        rg->_parent = this;
    }

    // если у текущего уже был один левый — отменяем его родительскую связь и вернем его
    Node* prevRight = _right;
    _right = rg;

    if (prevRight)
        prevRight->_parent = nullptr;

    return prevRight;
}


//==============================================================================
// class RBTree
//==============================================================================

template <typename Element, typename Compar >
RBTree<Element, Compar>::RBTree()
{
    _root = nullptr;
    _dumper = nullptr;
}

template <typename Element, typename Compar >
RBTree<Element, Compar>::~RBTree()
{
    // грохаем пока что всех через корень
    if (_root)
        delete _root;
}


template <typename Element, typename Compar >
void RBTree<Element, Compar>::deleteNode(Node* nd)
{
    // если переданный узел не существует, просто ничего не делаем, т.к. в вызывающем проверок нет
    if (nd == nullptr)
        return;

    // потомков убьет в деструкторе
    delete nd;
}


template <typename Element, typename Compar >
void RBTree<Element, Compar>::insert(const Element& key)
{
    // этот метод можно оставить студентам целиком
    Node* newNode = insertNewBstEl(key);

    // отладочное событие
    if (_dumper)
        _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_BST_INS, this, newNode);

    rebalance(newNode);

    // отладочное событие
    if (_dumper)
        _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_INSERT, this, newNode);

}




template <typename Element, typename Compar>
const typename RBTree<Element, Compar>::Node* RBTree<Element, Compar>::find(const Element& key)
{
    // TODO: метод реализуют студенты
    Node* cur = _root;
    while(cur)
    {
        Node* check = cur;
        if(key > check->_key)
            cur = cur->_right;
        if(key < check->_key)
            cur = cur->_left;
        if(key == check->_key)
            return cur;
    }
    return nullptr;
}

template <typename Element, typename Compar >
typename RBTree<Element, Compar>::Node* 
        RBTree<Element, Compar>::insertNewBstEl(const Element& key)
{
    // TODO: метод реализуют студенты
    if(find(key) != nullptr)
        throw std::invalid_argument("You can't insert already existing key");

    Node* insNode = new Node(key);
    insNode->setRed();

    if(!_root)
    {
        _root = insNode;
        _root->setBlack();
        return insNode;
    }
    Node* afterWhich = _root;
    while(afterWhich)
    {
        Node* check = afterWhich;
        if(afterWhich->_left == nullptr && afterWhich->_right == nullptr)
            break;
        if(key > check->_key)
            if(afterWhich->_right != nullptr)
                afterWhich = afterWhich->_right;
            else
                break;
        if( key < check->_key)
            if(afterWhich->_left != nullptr)
                afterWhich = afterWhich->_left;
            else
                break;
    }

    if(key > afterWhich->_key)
    {
        afterWhich->_right = insNode;
        insNode->_parent = afterWhich;
    } else if(key < afterWhich->_key)
    {
        afterWhich->_left = insNode;
        insNode->_parent = afterWhich;
    }
    return insNode;
}


template <typename Element, typename Compar >
typename RBTree<Element, Compar>::Node* 
    RBTree<Element, Compar>::rebalanceDUG(Node* nd)
{
    // TODO: этот метод студенты могут оставить и реализовать при декомпозиции балансировки дерева
    // В методе оставлены некоторые важные комментарии/snippet-ы


    // попадание в этот метод уже означает, что папа есть (а вот про дедушку пока не известно)
    //...
    Node* grand = nd->_parent->_parent;

    Node* uncle = nd->_parent->isRightChild() ? grand->_left : grand->_right; // для левого случая нужен правый дядя и наоборот.

    // если дядя такой же красный, как сам нод и его папа...
    if (uncle != nullptr && uncle->isRed())
    {
        // дядю и папу красим в черное
        // а дедушку — в коммунистические цвета
        uncle->setBlack();
        nd->_parent->setBlack();
        if(grand != _root)
            grand->setRed();
        // отладочное событие
        if (_dumper)
            _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_RECOLOR1, this, nd);

        // теперь чередование цветов "узел-папа-дедушка-дядя" — К-Ч-К-Ч, но надо разобраться, что там
        // с дедушкой и его предками, поэтому продолжим с дедушкой
        //..
        nd = grand;
        return nd;
    }

    // дядя черный
    // смотрим, является ли узел "правильно-правым" у папочки
    if (nd->isRightChild() && nd->_parent->isRightChild())     // right-right case
    {
        // CASE2 в действии
        rotLeft(grand);
        if(grand->isBlack())
            grand->setRed();
        else
            grand->setBlack();
        if(!nd->_parent)
        {
            nd->setBlack();
            return nd;
        }
        if(nd->_parent->isBlack())
            nd->_parent->setRed();
        else
            nd->_parent->setBlack();
        // ... при вращении будет вызвано отладочное событие
        // ...
        _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_LROT, this, nd);
    }
    else if(nd->isLeftChild() && nd->_parent->isLeftChild()) // left-left case
    {
        rotRight(grand);
        if(grand->isBlack())
            grand->setRed();
        else
            grand->setBlack();
        if(!nd->_parent)
        {
            nd->setBlack();
            return nd;
        }
        if(nd->_parent->isBlack())
            nd->_parent->setRed();
        else
            nd->_parent->setBlack();
    }
    else if(nd->isRightChild() && nd->_parent->isLeftChild()) //right-left case
    {
        rotLeft(nd->_parent);
        rotRight(grand);
        if(grand->isBlack())
            grand->setRed();
        else
            grand->setBlack();
        if(!nd->_parent)
        {
            nd->setBlack();
            return nd;
        }
        if(uncle == nullptr || uncle->isBlack())
        {
            nd->setBlack();
            return nd->_parent;
        }
        if(nd->_parent->isBlack())
            nd->_parent->setRed();
        else
            nd->_parent->setBlack();
    }
    else if(nd->_parent->isRightChild() && nd->isLeftChild()) // right left case
    {
        rotRight(nd->_parent);
        rotLeft(grand);
        if(grand->isBlack())
            grand->setRed();
        else
            grand->setBlack();
        if(!nd->_parent)
        {
            nd->setBlack();
            return nd;
        }
        if(uncle == nullptr || uncle->isBlack())
        {
            nd->setBlack();
            return nd->_parent;
        }
        if(nd->_parent->isBlack())
            nd->_parent->setRed();
        else
            nd->_parent->setBlack();
    }

    // ...

    // отладочное событие
    if (_dumper)
        _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_RECOLOR3D, this, nd);


    // деда в красный

    // ...

    // отладочное событие
    if (_dumper)
        _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_RECOLOR3G, this, nd);

    // ...


    return nd;
}


template <typename Element, typename Compar >
void RBTree<Element, Compar>::rebalance(Node* nd)
{
    // TODO: метод реализуют студенты

    // ...

    // пока папа — цвета пионерского галстука, действуем
    while (nd != _root && nd->isDaddyRed())
    {
        // локальная перебалансировка семейства "папа, дядя, дедушка" и повторная проверка
        nd = rebalanceDUG(nd);
    }


    // ...
}



template <typename Element, typename Compar>
void RBTree<Element, Compar>::rotLeft(typename RBTree<Element, Compar>::Node* nd)
{
    // TODO: метод реализуют студенты

    // правый потомок, который станет после левого поворота "выше"
    Node* y = nd->_right;

    if (!y)
        throw std::invalid_argument("Can't rotate left since the right child is nil");

    if (y->_left)
    {
        nd->_right = y->_left;
        y->_left->_parent = nd;
    }
    else
        nd->_right = nullptr;

    if (nd->_parent)
        y->_parent = nd->_parent;
    if (nd->_parent == nullptr)
    {
        _root = y;
        y->_parent = nullptr;
    }
    else
    {
        if (!nd->isRightChild())
            nd->_parent->_left = y;
        else
            nd->_parent->_right = y;
    }

    y->_left = nd;
    nd->_parent = y;

    // ...


    // отладочное событие
    if (_dumper)
        _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_LROT, this, nd);
}



template <typename Element, typename Compar>
void RBTree<Element, Compar>::rotRight(typename RBTree<Element, Compar>::Node* nd)
{
    // TODO: метод реализуют студенты
    Node* y = nd->_left;

    if (!y)
        throw std::invalid_argument("Can't rotate left since the left child is nil");


    if (y->_right != nullptr)
    {
        nd->_left = y->_right;
        y->_right->_parent = nd;
    }
    else
        nd->_left = nullptr;

    if (nd->_parent != nullptr)
        y->_parent = nd->_parent;

    if (nd->_parent == nullptr)
    {
        _root = y;
        y->_parent = nullptr;
    }
    else
    {
        if (!nd->isRightChild())
            nd->_parent->_left = y;
        else
            nd->_parent->_right = y;
    }

    y->_right = nd;
    nd->_parent = y;


    // отладочное событие
    if (_dumper)
        _dumper->rbTreeEvent(IRBTreeDumper<Element, Compar>::DE_AFTER_RROT, this, nd);
}


} // namespace xi


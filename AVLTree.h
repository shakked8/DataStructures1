#ifndef AVLTREE_AVLTREE_H
#define AVLTREE_AVLTREE_H

#define SPACE 10
#include <iostream>

template <class T>
class Node
{

public:
    int m_value;
    T* m_object;
    Node* m_left;
    Node* m_right;
    Node* strengthNode;

    Node(int value, T* object, Node* node = nullptr);
};

template <class T>
class AVLTree
{
    Node<T>* m_root;

public:

    Node<T>* root() const;

    AVLTree();

    bool isEmpty() const;

    int getHeight(Node<T>* r) const;

    int getBalanceFactor(Node<T>* n) const;

    Node<T>* rightRotate(Node<T>* y);

    Node<T>* leftRotate(Node<T>* x);

//    void insert(Node<T>* r, Node<T>* new_node);
    void insert(Node<T>* new_node);

    Node<T>* minValueNode() const;
    Node<T>* maxValueNode() const;

    void deleteNode(Node<T>*);
    Node<T>* doDeleteNode(Node<T>* r);

    void print2D(Node<T>* r, int space) const;

    void deleteTree(Node<T>* r);

    Node<T>* recursiveSearch(Node<T>* r, int val) const;
    Node<T>* findNode(int val) const;

    bool isNodeInTree(int val) const;

    Node<T>* doInsert(Node<T>* r, Node<T>* new_node);
};

template<class T>
Node<T> *AVLTree<T>::root() const{
    return m_root;
}


// Node implementation

template <class T>
Node<T>::Node(int v, T* object, Node* node)
{
    m_value = v;
    m_object = object;
    m_left = nullptr;
    m_right = nullptr;
    strengthNode = node;
}

// AVLTree implementation

template <class T>
AVLTree<T>::AVLTree()
{
    m_root = nullptr;
}

template <class T>
bool AVLTree<T>::isEmpty() const
{
    if(m_root == nullptr)
    {
        return true;
    }

    else
    {
        return false;
    }
}

template <class T>
int AVLTree<T>::getHeight(Node<T>* r) const
{
    if(r == nullptr)
    {
        return -1;
    }

    else
    {
        int leftHeight = getHeight(r->m_left);
        int rightHeight = getHeight(r->m_right);

        return leftHeight > rightHeight? (leftHeight + 1) : (rightHeight + 1);
    }
}

template <class T>
int AVLTree<T>::getBalanceFactor(Node<T>* n) const
{
    if(n == nullptr)
    {
        return -1;
    }

    return getHeight(n->m_left) - getHeight(n->m_right);
}

template <class T>
Node<T>* AVLTree<T>::rightRotate(Node<T>* y)
{
    Node<T>* x = y->m_left;
    Node<T>* T2 = x->m_right;

    // Perform rotation
    x->m_right = y;
    y->m_left = T2;

    return x;
}

template <class T>
Node<T>* AVLTree<T>::leftRotate(Node<T>* x)
{
    Node<T>* y = x->m_right;
    Node<T>* T2 = y->m_left;

    y->m_left = x;
    x->m_right = T2;

    return y;
}

template <class T>
Node<T>* AVLTree<T>::doInsert(Node<T>* r, Node<T>* new_node){
    if(r == nullptr)
    {
        r = new_node;
        return r;
    }

    if(new_node->m_value < r->m_value)
    {
        r->m_left = doInsert(r->m_left, new_node);
    }

    else if(new_node->m_value > r->m_value)
    {
        r->m_right = doInsert(r->m_right, new_node);
    }

    else
    {
        return r;
    }

    int bf = getBalanceFactor(r);
    if(bf > 1 && new_node->m_value < r->m_left->m_value)
    {
        return rightRotate(r);
    }

    if(bf < -1 && new_node->m_value > r->m_right->m_value)
    {
        return leftRotate(r);
    }

    if(bf > 1 && new_node->m_value > r->m_left->m_value)
    {
        r->m_left = leftRotate(r->m_left);
        return rightRotate(r);
    }

    if(bf < -1 && new_node->m_value < r->m_right->m_value)
    {
        r->m_right = rightRotate(r->m_right);
        return leftRotate(r);
    }

    return r;
}
template <class T>
void AVLTree<T>::insert(Node<T>* new_node)
{
    m_root = doInsert(root(),new_node);
}

template <class T>
Node<T>* AVLTree<T>::minValueNode() const
{
    Node<T> * current = m_root;

    while (current -> m_left != nullptr)
    {
        current = current -> m_left;
    }
    return current;
}
template <class T>
Node<T>* AVLTree<T>::maxValueNode() const
{
    Node<T> * current = m_root;

    while (current -> m_right != nullptr)
    {
        current = current -> m_right;
    }
    return current;
}

template <class T>
void AVLTree<T>::deleteNode(Node<T>* r){
    m_root = doDeleteNode(r);
}

template <class T>
Node<T>* AVLTree<T>::doDeleteNode(Node<T>* r)
{
    //TODO fix the deletenode function
//
//    if(r->m_left == nullptr)
//    {
//        Node<T>* temp = r->m_right;
//        delete r;
//        return temp;
//    }
//
//    else if(r->m_right == nullptr)
//    {
//        Node<T>* temp = r->m_left;
//        delete r;
//        return temp;
//    }
//
//    else
//    {
//        Node<T>* temp = minValueNode(r->m_right);
//        r->m_value = temp->m_value;
//        r->m_right = doDeleteNode(r->m_right, temp->m_value);
//    }
//
//
//
//    int bf = getBalanceFactor(r);
//
//    if(bf == 2 && getBalanceFactor(r->m_left) >= 0)
//    {
//        return rightRotate(r);
//    }
//
//    else if(bf == 2 && getBalanceFactor(r->m_left) == -1)
//    {
//        r->m_left = leftRotate(r->m_left);
//        return rightRotate(r);
//    }
//
//    else if(bf == -2 && getBalanceFactor(r->m_left) <= 0)
//    {
//        return leftRotate(r);
//    }
//
//    else if(bf == -2 && getBalanceFactor(r->m_left) == 1)
//    {
//        r->m_right = rightRotate(r->m_right);
//        return leftRotate(r);
//    }
//
//    return r;

}
template <class T>
void AVLTree<T>::print2D(Node<T>* r, int space) const
{
    if(r == nullptr)
    {
        return;
    }

    space += SPACE;
    print2D(r->m_right, space);
    std::cout << std::endl;
    for(int i = SPACE; i < space; i++)
    {
        std::cout << " ";
    }
    std::cout << r->m_value << "\n";
    print2D(r->m_left, space);

}

template <class T>
Node<T>* AVLTree<T>::recursiveSearch(Node<T>* r, int val) const
{
    if(r == nullptr || r->m_value == val)
    {
        return r;
    }

    else if(val < r->m_value)
    {
        return recursiveSearch(r->m_left, val);
    }

    else
    {
        return recursiveSearch(r->m_right, val);
    }
}

template <class T>
Node<T>* AVLTree<T>::findNode(int val) const{
    return recursiveSearch(root(),val);
}

template <class T>
bool AVLTree<T>::isNodeInTree(int val) const
{
    if(recursiveSearch(m_root,val)== nullptr){
        return false;
    }
    return true;
}

template <class T>
void AVLTree<T>::deleteTree(Node<T>* r)
{
    if (r == nullptr)
    {
        return;
    }

    deleteTree(r->m_left);
    deleteTree(r->m_right);

    delete r->m_object;

    r->m_object = nullptr;

    delete r;
}



#endif //AVLTREE_AVLTREE_H

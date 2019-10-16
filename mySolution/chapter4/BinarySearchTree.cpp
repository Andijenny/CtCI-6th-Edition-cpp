#include "tree.hpp"
#include <cstdlib>
#include <ctime>

using namespace std;
namespace bst
{
template<typename T, template<typename T1> class Node = treeNode>
class BinarySearchTree{
public:
    using NodePtr = typename Node<T>::NodePtr;

    decltype(auto) insert(T v);

    decltype(auto) getRandomNode();

    decltype(auto) at(size_t idx) {
        if(idx > m_size) throw;
        size_t i = 1;
        return traversal(m_root, i, idx);
    }
    const NodePtr& getRoot() const {return m_root;}
    decltype(auto) find(T v) {
        return find(m_root, v);
    }

    void deletion(T v) {
        NodePtr curNode = find(m_root, v);
        if(!curNode) return;
        m_size--;
        if(!curNode->getLeft()) {
            if(curNode->getRight())
                setNode(curNode, curNode->getRight());
            else
                setNode(curNode, NodePtr());
            return;
        }
        NodePtr left = curNode->getLeft();
        while(left->getRight()) {
            left = left->getRight();
        }
        if(left->getLeft()) {
           setNode(left, left->getLeft());
        }
        setNode(curNode, left);
    }

    void print2D() const {
        return tree<T>::print2DUtil(m_root, 0, 2);
    }
private:
    NodePtr         m_root;
    size_t          m_size = 0;

private:
    decltype(auto) insert(const NodePtr& node, T v);

    NodePtr traversal(const NodePtr& node, size_t& i, size_t stopIdx) {
        if(i == stopIdx)
            return node;
        NodePtr next;
        if(node->getLeft())
            next = traversal(node->getLeft(), ++i, stopIdx);
        if(i != stopIdx && node->getRight())
            next = traversal(node->getRight(), ++i, stopIdx);
        return next;
    }

    decltype(auto) find(const NodePtr& node, T v);

    void setNode(const NodePtr& oldNode, const NodePtr& newNode) {
        NodePtr parent = oldNode->getParent();
        if(oldNode->getValue() == parent->getLeft()->getValue()) {
            parent->setLeftChild(newNode);
        }
        else {
            parent->setRightChild(newNode);
        }

        if(!newNode) return;

        if(newNode->getValue() == newNode->getParent()->getLeft()->getValue()) {
            newNode->getParent()->setLeftChild(NodePtr());
        }
        else {
            newNode->getParent()->setRightChild(NodePtr());
        }
        newNode->setParent(parent);
        if(oldNode->getLeft()->getValue() != newNode->getValue())
            newNode->setLeftChild(oldNode->getLeft());
        else
            newNode->setLeftChild(NodePtr());
        newNode->setRightChild(oldNode->getRight());
    }
};


//template<typename T, template<typename>class Node>
//using NodePtr = typename BinarySearchTree<T, Node>::NodePtr;

template<typename T, template<typename T1> class Node>
decltype(auto) BinarySearchTree<T, Node>::getRandomNode()
{
    if(m_size == 0) throw;
    srand(time(0));
    const size_t index = rand() % m_size + 1;
    return this->at(index);
}

template<typename T, template<typename T1> class Node>
decltype(auto) BinarySearchTree<T, Node>::insert(T v)
{
    m_size++;
    if(!m_root) {
        m_root = make_shared<Node<T>>(v, NodePtr());
        return m_root;
    }
    return insert(m_root, v);
}

template<typename T, template<typename T1> class Node>
decltype(auto) BinarySearchTree<T, Node>::insert(const NodePtr& node, T v)
{
    if(!node) return NodePtr();
    NodePtr p;
    if(v <= node->getValue()) {
        p = insert(node->getLeft(), v);
        if(!p)
            node->setLeftChild(make_shared<Node<T>>(v, node));
    }
    else {
        p = insert(node->getRight(), v);
        if(!p)
            node->setRightChild(make_shared<Node<T>>(v, node));
    }
    if(!p) p = node;

    return p;
}

template<typename T, template<typename T1> class Node>
decltype(auto) BinarySearchTree<T, Node>::find(const NodePtr& node, T v)
{
    if(!node) return NodePtr();
    NodePtr p;
    if(v == node->getValue()) {
        p = node;
    }
    else if(v < node->getValue()) {
        p = find(node->getLeft(), v);
    }
    else {
        p = find(node->getRight(), v);
    }
    if(!p) return NodePtr();

    return p;
}
}

int main()
{
    initializer_list<int> vec{8, 6, 10, 2, 4, 9, 19, 1};
    bst::BinarySearchTree<int> tree;
    for(auto it = vec.begin(); it != vec.end(); ++it) {
        tree.insert(*it);
    }
    tree.print2D();
    tree.deletion(6);
    cout << "after delete 6" << endl;
    tree.print2D();
    cout << "select randomly: " << tree.getRandomNode()->getValue() << endl;
}

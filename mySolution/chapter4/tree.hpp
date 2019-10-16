#pragma once

#include <iostream>
#include <memory>
#include <queue>
#include <string>

template<typename T>
class treeNode {
public:
    using NodePtr = std::shared_ptr<treeNode<T>>;
    treeNode(T&& v) : m_value(std::move(v))
    {
    }
    treeNode(const T& v) : m_value(v)
    {
    }
    treeNode(T&& v, const NodePtr& parent): m_value(std::move(v)), m_parent(parent)
    {
    }
    treeNode(const T& v, const NodePtr& parent) : m_value(v), m_parent(parent)
    {
    }
    NodePtr& getLeft()
    {
        return m_childs.first;
    }

    NodePtr& getRight()
    {
        return m_childs.second;
    }

    NodePtr getParent() const
    {
        auto sp = m_parent.lock();
        return sp;
    }
    const NodePtr& getLeft() const
    {
        return m_childs.first;
    }

    const NodePtr& getRight() const
    {
        return m_childs.second;
    }

    template<typename U>
    void setParent(U&& ptr)
    {
        m_parent = ptr;
    }

    template<typename U>
    void setLeftChild(U&& ptr)
    {
        m_childs.first = ptr;
    }

    template<typename U>
    void setRightChild(U&& ptr)
    {
        m_childs.second = ptr;
    }

    const T& getValue() {return m_value;}
private:
    T                               m_value;
    std::pair<NodePtr, NodePtr>     m_childs;
    std::weak_ptr<treeNode>         m_parent;
};

template<typename T, template<typename T1> class Node = treeNode>
class tree{
public:
    using NodePtr = typename Node<T>::NodePtr;
    template<typename U>
    void setRoot(U&& ptr)
    {
        m_root = ptr;
    }
    const NodePtr& getRoot() const
    {
        if(!isEmpty())
            return m_root;
        else
            throw("Empty trees");
    }
    NodePtr getLeftMost() const
    {
        auto node = m_root;
        while(node && node->getLeft()) {
            node = node->getLeft();
        }
        return node;
    }
    bool isEmpty() const
    {
        return !m_root;
    }
    void print() const
    {
       display(m_root);
       std::cout << std::endl;
    }
    void print2D() const
    {
        print2DUtil(m_root, 0, 2);
    }

    static void print2DUtil(const NodePtr& node, size_t space, const size_t COUNT)
    {
        if(!node) return;

        print2DUtil(node->getRight(), space + COUNT, COUNT);

        if(node->getRight()) {
            for(int i = space+COUNT-1; i > space; --i) {
                std::cout << std::string(i, ' ') << "/" << std::endl;
            }
        }
        std::cout << std::string(space, ' ') << node->getValue() << std::endl;
        if(node->getLeft()) {
            for(int i = space+1; i < space+COUNT; ++i) {
                std::cout << std::string(i, ' ') << "\\" << std::endl;
            }
        }
        print2DUtil(node->getLeft(), space + COUNT, COUNT);
    }
protected:
    NodePtr         m_root;
private:
    void display(const NodePtr& node) const
    {
        if(node && node->getLeft()) {
            display(node->getLeft());
        }
        if(node)
            std::cout << node->getValue() << " ";
        if(node && node->getRight())
            display(node->getRight());
    }

};

template<typename T>
using NodePtr = typename tree<T>::NodePtr;

template<bool WithParent = false>
class treeUtils{
public:
    template<typename Iter>
    static decltype(auto) createTrees(Iter bg, Iter ed)
    {
        using T = typename std::iterator_traits<Iter>::value_type;
        if(bg == ed) return NodePtr<T>();
        std::queue<NodePtr<T>> queue;
        auto root = std::make_shared<treeNode<T>>(*bg);
        std::advance(bg, 1);
        queue.push(root);
        while(!queue.empty()) {
            auto curNode = queue.front();
            queue.pop();

            if(bg == ed) continue;
            auto left = std::make_shared<treeNode<T>>(*bg);
            curNode->setLeftChild(left);
            queue.push(left);

            std::advance(bg, 1);
            if(bg == ed) continue;
            auto right = std::make_shared<treeNode<T>>(*bg);
            curNode->setRightChild(right);
            queue.push(right);
            std::advance(bg, 1);
        }
        return root;
    }
};

template<> class treeUtils<true>
{
public:
    template<typename Iter>
    static decltype(auto) createTrees(Iter bg, Iter ed)
    {
        using T = typename std::iterator_traits<Iter>::value_type;
        if(bg == ed) return NodePtr<T>();
        std::queue<NodePtr<T>> queue;
        auto root = std::make_shared<treeNode<T>>(*bg, NodePtr<T>());
        std::advance(bg, 1);
        queue.push(root);
        while(!queue.empty()) {
            auto curNode = queue.front();
            queue.pop();

            if(bg == ed) continue;
            auto left = std::make_shared<treeNode<T>>(*bg, curNode);
            curNode->setLeftChild(left);
            queue.push(left);

            std::advance(bg, 1);
            if(bg == ed) continue;
            auto right = std::make_shared<treeNode<T>>(*bg, curNode);
            curNode->setRightChild(right);
            queue.push(right);
            std::advance(bg, 1);
        }
        return root;
    }
};

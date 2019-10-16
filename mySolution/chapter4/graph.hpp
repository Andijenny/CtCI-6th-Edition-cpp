#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <exception>
#include <unordered_set>
#include <unordered_map>
#include <deque>

template<typename T>
struct WeakPtrHash : public std::unary_function<std::weak_ptr<T>, size_t>
{
    size_t operator()(const std::weak_ptr<T>& wp) const
    {
        auto sp = wp.lock();
        return std::hash<decltype(sp)>()(sp);
    }
};

template<typename T>
struct WeakPtrEqual : public std::unary_function<std::weak_ptr<T>, bool>
{
    bool operator()(const std::weak_ptr<T>& left, const std::weak_ptr<T>& right) const
    {
        return !left.owner_before(right) && !right.owner_before(left);
    }
};

enum class State : int {
    UNVISITED = 0,
    VISITING,
    VISITED
};


class CycleDependencyException : public std::exception {
    public:
        const char* what() {
            return "A dependency cycle detected";
        }
};

class SNode {
public:
    SNode(const std::string& n) : m_name(n), m_state(State::UNVISITED)
    {
    }
    void addAdjacent(const std::shared_ptr<SNode>& others)
    {
        m_adj.insert(others);
    }
    bool isAdjacent(const std::shared_ptr<SNode>& key)
    {
        return m_adj.find(key) != m_adj.end();
    }
    const std::unordered_set<std::weak_ptr<SNode>, WeakPtrHash<SNode>, WeakPtrEqual<SNode>>& getAdjacent()
    {
        return m_adj;
    }
    ~SNode()
    {
    }

    mutable State               m_state;
    std::string                 m_name;
private:
    std::unordered_set<std::weak_ptr<SNode>, WeakPtrHash<SNode>, WeakPtrEqual<SNode>>  m_adj;
};

class DNode {
public:
    DNode(const std::string& n) : m_name(n)
    {
    }
    void addFrom(const std::shared_ptr<DNode>& others)
    {
        m_from.insert(others);
    }
    void addTo(const std::shared_ptr<DNode>& others)
    {
        m_to.insert(others);
    }
    std::unordered_set<std::weak_ptr<DNode>, WeakPtrHash<DNode>, WeakPtrEqual<DNode>>& getFrom()
    {
        return m_from;
    }
    std::unordered_set<std::weak_ptr<DNode>, WeakPtrHash<DNode>, WeakPtrEqual<DNode>>& getTo()
    {
        return m_to;
    }
    ~DNode()
    {
    }

    std::string                 m_name;
private:
    std::unordered_set<std::weak_ptr<DNode>, WeakPtrHash<DNode>, WeakPtrEqual<DNode>>  m_to;
    std::unordered_set<std::weak_ptr<DNode>, WeakPtrHash<DNode>, WeakPtrEqual<DNode>>  m_from;
};

template<typename Node = SNode>
class Graph {
public:
    std::shared_ptr<Node>& addNode(const std::string& name = std::string())
    {
        m_nodes.emplace_back(std::make_shared<Node>(name));
        if(!name.empty())
            m_nameNodes[name] = m_nodes.back();
        return m_nodes.back();
    }
    const std::shared_ptr<Node>& operator[](size_t i) const
    {
        return m_nodes[i];
    }
    const std::shared_ptr<Node>& operator[](const std::string& name) const
    {
        return m_nameNodes.at(name);
    }
    const std::deque<std::shared_ptr<Node>>& getNodes() const
    {
        return m_nodes;
    }
    std::deque<std::shared_ptr<Node>>& getNodes()
    {
        return m_nodes;
    }
private:
    std::deque<std::shared_ptr<Node>>       m_nodes;
    std::unordered_map<std::string, std::shared_ptr<Node>>  m_nameNodes;
};

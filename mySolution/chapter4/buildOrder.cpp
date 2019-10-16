#include <iostream>
#include <list>
#include <string>
#include <memory>
#include <stack>
#include "graph.hpp"

using namespace std;

template<typename Node>
decltype(auto) buildOrder(const initializer_list<string>& nodes, const initializer_list<array<const string, 2>>& adjs)
{
    using NodePtr = std::shared_ptr<DNode>;
    Graph<Node> g;
    for(const auto& i : nodes)
        g.addNode(i);
    for(auto& d : adjs) {
        g[d[0]]->addFrom(g[d[1]]);
        g[d[1]]->addTo(g[d[0]]);
    }

    auto& deque = g.getNodes();
    list<NodePtr> list;
    size_t cycle = deque.size();
    size_t counts = 0;
    while(!deque.empty()) {
        if(counts == cycle) {
            if(counts == deque.size()) {
                throw CycleDependencyException();
            }
            else {
                counts = 0;
                cycle = deque.size();
            }
        }

        counts++;
        const NodePtr& cur = deque.front();
        deque.pop_front();
        if(cur->getFrom().empty()) {
            list.push_back(cur);
            for(auto& n : cur->getTo()) {
                auto& sets = n.lock()->getFrom();

                std::weak_ptr<Node> wp(cur);
                auto it2 = sets.find(wp);
                if(it2 != sets.end())
                    sets.erase(it2);
            }
        }
        else {
            deque.push_back(cur);
        }
    }
    return list;
}

template<>
decltype(auto) buildOrder<SNode>(const initializer_list<string>& nodes, const initializer_list<array<const string, 2>>& adjs)
{
    using NodePtr = std::shared_ptr<SNode>;
    Graph<SNode> g;
    for(const auto& i : nodes)
        g.addNode(i);
    for(auto& d : adjs) {
        g[d[1]]->addAdjacent(g[d[0]]);
    }

    list<NodePtr> list;
    stack<NodePtr> stack;
    for(const auto& cur : g.getNodes()) {
        if(cur->m_state == State::UNVISITED)
            stack.push(cur);
        while(!stack.empty()) {
            const auto& n = stack.top();
            stack.pop();

            if(n->getAdjacent().empty() || n->m_state == State::VISITED) {
                list.push_front(n);
                n->m_state = State::VISITED;
                continue;
            }

            if(n->m_state == State::VISITING)
                throw CycleDependencyException();

            stack.push(n);
            n->m_state = State::VISITED;

            for(const auto& d : n->getAdjacent()) {
                auto sp = d.lock();
                if(sp->m_state != State::VISITED) {
                    sp->m_state = State::VISITING;
                    stack.push(sp);
                }
            }

        }
    }
    return list;
}

int main()
{
    initializer_list<string> nodes{"a", "c", "b", "d", "e", "f"};
    initializer_list<array<const string, 2>> adjs{{"c","f"}, {"b","f"}, {"a","f"},{"a", "c"},{"a","b"},{"e","a"},{"e","b"}};
    auto list = buildOrder<SNode>(nodes, adjs);
    for(const auto& i : list)
        cout << i->m_name << "->";
    cout << "NULL" << endl;
}

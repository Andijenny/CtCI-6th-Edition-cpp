#include <iostream>
#include <list>
#include <string>
#include <memory>
#include <queue>
#include "graph.hpp"

using namespace std;

template<typename G, typename Node>
bool routeBetweenNodes(const G& g, const Node& start, const Node& end)
{
    if(start == end) return true;
    std::queue<Node> queue;

    start->m_state = State::VISITING;
    queue.push(start);

    while(!queue.empty()) {
        const Node& cur = queue.front();
        queue.pop();
        for(auto& i : cur->getAdjacent()) {
            auto sp = i.lock();
            if(sp && sp->m_state == State::UNVISITED) {
                if(sp == end) {
                    return true;
                }
                else {
                    sp->m_state = State::VISITING;
                    queue.push(sp);
                }
            }
        }
        cur->m_state = State::VISITED;
    }
    return false;
}

int main()
{
    initializer_list<string> nodes{"a", "c", "b", "d"};
    initializer_list<array<const string, 2>> adjs{{"a","b"}, {"a","c"}, {"c","b"},{"c", "d"}};
    Graph<SNode> g;
    for(const auto& i : nodes)
        g.addNode(i);
    for(auto& d : adjs)
        g[d[0]]->addAdjacent(g[d[1]]);
    cout << boolalpha << routeBetweenNodes(g, g["b"], g["d"]) << endl;
}

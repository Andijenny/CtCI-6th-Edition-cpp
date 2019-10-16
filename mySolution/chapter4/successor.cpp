#include "tree.hpp"

#include <queue>

using namespace std;
template<typename Node>
Node successor(const Node& node)
{
    Node cur = node;
    if(cur->getRight()) return cur->getRight();

    while(cur && cur->getParent() && cur->getParent()->getRight() == cur) {
        cur = cur->getParent();
    }

    if(!cur) return Node();

    return cur->getParent();
}

int main()
{
    initializer_list<int> vec({8, 3, 9, 2, 4, 9, 11, 1});
    tree<int> tree;
    tree.setRoot(treeUtils<true>::createTrees(vec.begin(), vec.end()));
    const auto& leftNode = tree.getLeftMost();
    tree.print2D();
    size_t depth;

    const auto& cur = leftNode->getParent()->getParent()->getParent()->getRight()->getLeft();
    auto node = successor(cur);
    if(node)
        cout << "successor of " << cur->getValue() << ": " << node->getValue()  << endl;
}

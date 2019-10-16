#include "tree.hpp"

using namespace std;
template<typename Node>
bool isSubTree(const Node& bigger, const Node& smaller)
{
    if(!bigger || !smaller) {
        return (!bigger && !smaller) ? true : false;
    }
    if(bigger->getValue() == smaller->getValue()) {
        if(isSubTree(bigger->getLeft(), smaller->getLeft()) && isSubTree(bigger->getRight(), smaller->getRight()))
        return true;
    }

    return false;
}

template<typename Node>
bool subTree(const Node& bigger, const Node& smaller)
{
    if(!bigger) return false;
    if(bigger->getValue() == smaller->getValue() && isSubTree(bigger, smaller))
        return true;
    return subTree(bigger->getLeft(), smaller) || subTree(bigger->getRight(), smaller);
}

int main()
{
    initializer_list<int> vec{8, 6, 10, 2, 4, 9, 19, 1, 21, 17, 14, 15, 5, 3, 7, 11, 13, 20};
    tree<int> tree;
    tree.setRoot(treeUtils<true>::createTrees(vec.begin(), vec.end()));
    tree.print2D();
    auto node = tree.getLeftMost()->getParent()->getParent()->getParent()->getRight();
    auto res = subTree(tree.getRoot(), node);
    cout << "Is " << node->getValue() << " a sub-tree of " << tree.getRoot()->getValue() << "? " << boolalpha << res << endl;
}

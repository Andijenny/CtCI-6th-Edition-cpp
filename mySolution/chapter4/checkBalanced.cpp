#include "tree.hpp"

using namespace std;
template<typename Node>
bool checkBalanced(const Node& root, size_t& depth)
{
    if(!root) {
        depth = 0;
        return true;
    }
    size_t dL, dR;
    bool lb = checkBalanced(root->getLeft(), dL);
    bool rb = checkBalanced(root->getRight(), dR);
    depth =  (dL > dR ? dL : dR) + 1;

    const size_t diffD = dL > dR ? dL - dR : dR - dL;
    return lb && rb && diffD <= 1;
}

int main()
{
    initializer_list<int> vec({1, 3, 4, 5, 7, 9, 11, 12});
    tree<int> tree;
    tree.setRoot(treeUtils<false>::createTrees(vec.begin(), vec.end()));
    const auto& leftNode = tree.getLeftMost();
    leftNode->setLeftChild(std::make_shared<treeNode<int>>(8));
    tree.print2D();

    size_t depth;
    cout << "is balanced ?  "  << boolalpha << checkBalanced(tree.getRoot(), depth)  << endl;
}

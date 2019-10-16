#include "tree.hpp"
#include <cmath>
#include <limits>

using namespace std;


constexpr int NULL_INT = std::numeric_limits<int>::max();

template<typename T>
bool validateBST(const NodePtr<T>& root, T min, T max)
{
    if(!root) return true;

    const T& val = root->getValue();
    if((min != NULL_INT && min >= val) || (max != NULL_INT && max < val)) {
        return false;
    }

    if(!validateBST(root->getLeft(), min, val) || !validateBST(root->getRight(), val, max))
        return false;

    return true;
}

int main()
{
    initializer_list<int> vec({8, 3, 9, 2, 4, 9, 11, 1});
    tree<int> tree;
    tree.setRoot(treeUtils<false>::createTrees(vec.begin(), vec.end()));
    tree.print2D();

    cout << "is valid BST ?  "  << boolalpha << validateBST<int>(tree.getRoot(), NULL_INT, NULL_INT)  << endl;
}

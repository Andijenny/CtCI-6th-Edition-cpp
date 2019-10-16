#include "tree.hpp"

#include <vector>

using namespace std;

template<typename Iter>
decltype(auto) createMinBST(Iter bg, const NodePtr<typename std::iterator_traits<Iter>::value_type>& parent, size_t lo, size_t hi)
{
    using T = typename std::iterator_traits<Iter>::value_type;
    if(hi == lo) return NodePtr<T>();
    size_t mid = (lo + hi)/2;
    auto it = bg;
    advance(it, mid);
    auto curRoot = std::make_shared<treeNode<T>>(*it, parent);
//    std::cout << parent.use_count() << std::endl;
    auto leftChild = createMinBST(bg, curRoot, lo, mid);
    auto rightChild = createMinBST(bg, curRoot, mid+1, hi);
    if(leftChild)
      curRoot->setLeftChild(leftChild);
    if(rightChild)
      curRoot->setRightChild(rightChild);
    return curRoot;
}


template<typename Iter>
decltype(auto) minimalTree(Iter bg, size_t size)
{
    return createMinBST(bg, nullptr, 0, size);
}

int main()
{
    vector<int> vec{1, 3, 4, 5, 8, 9};
    vector<int>::const_iterator bg = vec.begin();
    tree<int> bst;
    bst.setRoot(minimalTree(bg, vec.size()));
    bst.print();
}

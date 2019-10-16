#include "tree.hpp"

using namespace std;
template<typename Node>
size_t depth(const Node& n)
{
    size_t depth = 0;
    Node cur = n;
    while(cur->getParent()) {
        cur = cur->getParent();
        depth++;
    }
    return depth;
}

template<typename Node>
decltype(auto) firstCommonAncestor(const Node& n1, const Node& n2)
{
   Node ptr1 = n1, ptr2 = n2;
   size_t d1 = depth(n1);
   size_t d2 = depth(n2);
   if(d1 > d2) {
       size_t diff = d1 - d2;
       while(diff-- > 0) {
           ptr1 = ptr1->getParent();
       }
   }
   else {
       size_t diff = d2 - d1;
       while(diff-- > 0) {
           ptr2 = ptr2->getParent();
       }
   }
   size_t diff = d1 > d2 ? d2 : d1;
   while(diff > 0) {
       if(ptr1 == ptr2) break;
       ptr1 = ptr1->getParent();
       ptr2 = ptr2->getParent();
   }
   return ptr1;
}

enum class CoverResult
{
    EQUAL,
    LEFT,
    RIGHT,
    NOTFOUNT
};
template<typename Node>
CoverResult cover(const Node& root, const Node& child)
{
    if(!root) return CoverResult::NOTFOUNT;
    if(root == child) return CoverResult::EQUAL;
    if(cover(root->getLeft(), child) != CoverResult::NOTFOUNT)
        return CoverResult::LEFT;
    if(cover(root->getRight(), child) != CoverResult::NOTFOUNT)
        return CoverResult::RIGHT;

    return CoverResult::NOTFOUNT;
}

template<typename Node>
Node firstCommonAncestorNoParent(const Node& root, const Node& p, const Node& q)
{
    CoverResult pCover = cover(root, p);
    CoverResult qCover = cover(root, q);
    if(!root || pCover == CoverResult::NOTFOUNT
             || qCover == CoverResult::NOTFOUNT)
        return Node();
    if(pCover == CoverResult::EQUAL && qCover == CoverResult::EQUAL)
        return root;

    Node parent = root;
    while(pCover == qCover) {
        if(pCover == CoverResult::LEFT){
            parent = root->getLeft();
            pCover = cover(parent, p);
            qCover = cover(parent, q);
        }
        else {
            parent = root->getRight();
            pCover = cover(parent, p);
            qCover = cover(parent, q);
        }
    }
    return parent;
}

int main()
{
    initializer_list<int> vec{3, 5, 13, 0, 11, 14, 19, 80, 24, 55, 90, 6, 1, 2, 7, 9};
    tree<int> tree;
    tree.setRoot(treeUtils<true>::createTrees(vec.begin(), vec.end()));
    tree.print2D();
    const auto& node1 = tree.getRoot()->getLeft()->getLeft()->getLeft();
    const auto& node2 = tree.getRoot()->getRight();
 //   auto commonNode = firstCommonAncestor(node1, node2);
    auto commonNode = firstCommonAncestorNoParent(tree.getRoot(), node1, node2);
    cout << "common ancestor of " << node1->getValue() << " and " << node2->getValue() << ": " << commonNode->getValue() << endl;
}

#include <list>
#include <vector>
#include "tree.hpp"

using namespace std;

template<typename T>
void depthListsRec(const NodePtr<T>& node, size_t depth, vector<list<NodePtr<T>>>& dplist)
{
    if(!node) return;
    if(dplist.size() == depth) dplist.push_back(list<NodePtr<T>>());
    auto& list = dplist[depth];
    list.push_back(node);
    depthListsRec<T>(node->getLeft(), depth+1, dplist);
    depthListsRec<T>(node->getRight(), depth+1, dplist);
}

template<typename T>
void depthLists(const NodePtr<T>& root, vector<list<NodePtr<T>>>& dplist)
{
    depthListsRec<T>(root, 0, dplist);
}


int main()
{
    initializer_list<int> vec{3, 5, 3, 0, 11, 14, 19, 80, 24, 55, 90,6, 1, 2, 7, 9};
    tree<int> tree;
    tree.setRoot(treeUtils<false>::createTrees(vec.begin(), vec.end()));
    tree.print2D();
    vector<list<NodePtr<int>>> dplist;
    depthLists<int>(tree.getRoot(), dplist);
    for(const auto& v : dplist) {
        for(auto it = v.begin(); it != v.end(); ++it) {
            cout << (*it)->getValue() << "->";
        }
        cout << "NULL" << endl;
    }
}

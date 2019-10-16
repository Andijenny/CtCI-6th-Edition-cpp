#include "tree.hpp"
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

template<typename T1, typename T2>
void weaveLists(const T1& first, const T1& second, T2&& prefix, vector<T1>& sets)
{
    //using List = typename std::remove_cv<typename std::remove_reference<T1>::type>::type;
    using List = T1;
    List newPrefix(forward<T2>(prefix));

    if(first.empty() || second.empty()) {
        const auto& lists = first.empty() ? second : first;
        newPrefix.insert(newPrefix.end(), lists.begin(), lists.end());
        if(!newPrefix.empty())
            sets.push_back(newPrefix);
        return;
    }

    List rmHeadFirst(first);
    typename List::value_type vf = rmHeadFirst.front();
    rmHeadFirst.pop_front();
    newPrefix.push_back(vf);
    weaveLists(rmHeadFirst, second, newPrefix, sets);

    List rmHeadSecond(second);
    typename List::value_type vs = rmHeadSecond.front();
    rmHeadSecond.pop_front();
    newPrefix.pop_back();
    newPrefix.push_back(vs);
    weaveLists(first, rmHeadSecond, newPrefix, sets);
}

template<typename T, typename Node>
void bstSeqRec(const Node& node, vector<list<T>>& sets)
{
    if(!node->getLeft() && !node->getRight()) {
        sets.push_back(list<T>({node->getValue()}));
        return;
    }

    vector<list<T>> lset, rset;
    if(node->getLeft()) {
        bstSeqRec(node->getLeft(), lset);
    }
    if(node->getRight()) {
        bstSeqRec(node->getRight(), rset);
    }
    if(!node->getLeft()) {
        for(auto& r : rset)
            weaveLists(list<T>(), r, list<T>({node->getValue()}), sets);
    }
    if(!node->getRight()) {
        for(auto& l : lset)
            weaveLists(l, list<T>(), list<T>({node->getValue()}), sets);
    }
    for(auto& l : lset) {
        for(auto& r : rset) {
            weaveLists(l, r, list<T>({node->getValue()}) ,sets);
        }
    }
}

template<typename T, typename Node>
vector<list<T>> bstSequence(const Node& root)
{
    vector<list<T>> res;
    bstSeqRec(root, res);
    return res;
}

int main()
{
    initializer_list<int> vec{8, 6, 10, 2, 4, 9, 19, 1};
    tree<int> tree;
    tree.setRoot(treeUtils<false>::createTrees(vec.begin(), vec.end()));
    tree.print2D();
    auto res = bstSequence<int>(tree.getRoot());
    for(const auto& v : res) {
        for(auto it = v.begin(); it != v.end(); ++it) {
            if(it == v.begin()) {
                cout << "{";
            }
            else {
                cout << ",";
            }
            cout << (*it);
        }
        cout << "}" << endl;
    }
}

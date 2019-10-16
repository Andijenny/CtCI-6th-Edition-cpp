#include "tree.hpp"
#include <vector>
#include <algorithm>

using namespace std;

struct Result
{
    int value;
    int level{-1};
};


template<typename Node>
int travesalRec(const Node& node, vector<pair<int, int>>& vec)
{
    int l, r, re;
    if(node->getLeft()) {
        l = travesalRec(node->getLeft(), vec);
    } else {
        l = 0;
    }
    if(node->getRight()) {
        r = travesalRec(node->getRight(), vec);
    }
    else {
        r = 0;
    }
    if(!node->getLeft() && !node->getRight()) {
        re = 0;
    } else {
        re = (l > r ? l : r) + 1;
    }
    vec.emplace_back(re, node->getValue());
    return re;
}

template<typename Iter>
void binSort(Iter bg, Iter ed, vector<vector<int>>& binVec)
{
    for(auto it = bg; it != ed; ++it) {
        binVec[it->first].push_back(it->second);
    }
}

int factorial(size_t n) {
    if(n == 0) return 1;
    return n*factorial(n-1);
}
void permuteRec(vector<vector<int>>& binVec, vector<vector<int>>& permVec, int curh, int maxh)
{
    vector<vector<int>> vec1;
    if(curh == maxh) {
       permVec.push_back({binVec[maxh].back()});
       return;
    }
    permuteRec(binVec, vec1, curh+1, maxh);
    auto& vec = binVec[curh];
    const size_t psize = factorial(vec.size());
    permVec.resize(psize*vec1.size());
    for(size_t i = 0; i < vec1.size(); ++i) {
        int j = 0;
        do {
            size_t index = i*psize + j;
            j++;
            auto& vi = permVec[index];
            vi.insert(vi.end(), vec1[i].begin(), vec1[i].end());
            vi.insert(vi.end(), vec.begin(), vec.end());
        }while(next_permutation(vec.begin(), vec.end()));
    }
}

template<typename Node>
vector<vector<int>> bstSequence(const Node& root)
{
    using value_type = pair<int, int>;
    vector<value_type> vec;
    int height = travesalRec(root, vec);
    vector<vector<int>>  binVec(height + 1);
    binSort(vec.begin(), vec.end(), binVec);
    const size_t size = vec.size();
    vector<vector<int>> res;
    permuteRec(binVec, res, 0, height);
    return res;
}

int main()
{
    initializer_list<int> vec{8, 6, 10, 2, 4, 9, 19, 1};
    tree<int> tree;
    tree.setRoot(treeUtils<false>::createTrees(vec.begin(), vec.end()));
    tree.print2D();
    auto res = bstSequence(tree.getRoot());
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

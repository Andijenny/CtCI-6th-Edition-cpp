#include "tree.hpp"
#include <unordered_map>
#include <ctime>
#include <cstdlib>
using namespace std;

template<typename T>
int pathWithSum(const NodePtr<T>& node, int target, int sum, unordered_map<T, int> pathSum)
{
    if(!node) return 0;

    int totalPath = 0;
    sum += node->getValue();
    int over = sum - target;
    totalPath += pathSum.count(over)  ?  pathSum[over] : 0;
    if(sum == target) {
        totalPath++;
    }

    pathSum[sum] += 1;
    totalPath += pathWithSum(node->getLeft(), target, sum, pathSum);
    totalPath += pathWithSum(node->getRight(), target, sum, pathSum);
    if(pathSum[sum] == 1)
        pathSum.erase(sum);

    return totalPath;
}

template<typename T>
int pathWithSum(const NodePtr<T>& root, int target)
{
    unordered_map<int, int> pathSum;
    return pathWithSum(root, target, 0, pathSum);
}

int main()
{
//    vector<int> vec{-3,7,2,-2,13,-7,-2,1,3,-11,-1,5,11,-3,3,-5,2,-1,1,-7};
    vector<int> vec;
    srand(time(0));
    for(size_t i = 0; i < 8; ++i) {
        vec.push_back(rand()%8 - 4);
    }
    tree<int> tree;
    tree.setRoot(treeUtils<false>::createTrees(vec.begin(), vec.end()));
    tree.print2D();
    for(int i = -2; i < -1; i = i+1) {
        cout << pathWithSum<int>(tree.getRoot(), i) << " path that summed to " << i << endl;
    }
}

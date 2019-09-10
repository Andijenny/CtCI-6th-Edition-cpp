#include <iostream>
#include <list>
#include <unordered_set>
#include <string>
#include <sstream>

using namespace std;
void removeDups(list<int>& lists)
{
    unordered_set<int> cache;
    for(auto it = lists.begin(); it != lists.end();) {
        if(cache.find(*it) == cache.end()) {
            cache.emplace(*it);
            ++it;
        }
        else {
            it = lists.erase(it);
        }
    }
}

int main()
{
    size_t N;
    cout << "input N: ";
    cin >> N;
    getchar();
    list<int> lists;
    string str;
    cout << "input lists: ";
    getline(cin, str);
    istringstream itr(str);
    for(size_t i = 0; i < N; ++i) {
        int num;
        itr >> num;
        lists.push_back(num);
    }
    removeDups(lists);
    cout << "remove duplicates" << endl;
    for(auto i : lists)
        cout << i << " ";
    cout << endl;
}

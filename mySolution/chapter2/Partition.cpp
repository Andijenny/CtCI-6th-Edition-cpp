#include <iostream>
#include <string>
#include <sstream>
#include "List.h"

using namespace std;

void partition(List* pLists, int val)
{
    List slists, llists;
    Node* cur = pLists->_root;
    while(cur != nullptr) {
        if(cur->_ele < val)
            slists.add(cur);
        else
            llists.add(cur);
        cur = cur->next;
    }
    if(slists._tail != nullptr)
        slists.add(&llists);
    pLists->_root = slists._root;
    pLists->_tail = llists._tail;
    slists._root = nullptr;
    llists._root = nullptr;
}

int main()
{
    cout << "input N: ";
    size_t N;
    cin >> N;
    getchar();
    cout << "input lists: ";
    string str;
    getline(cin, str);
    istringstream itr(str);
    List lists;
    for(size_t i = 0; i < N; ++i) {
        int num;
        itr >> num;
        lists.add(num);
    }
    Node* cur = lists._root;
    int val;
    cout << "partition value: ";
    cin >> val;
    partition(&lists, val);
    cout << "after partition: ";
    lists.display();
}

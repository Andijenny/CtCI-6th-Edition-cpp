#include <iostream>
#include <string>
#include <sstream>
#include "List.h"

using namespace std;

bool palindrome(BList* pLists)
{
    Node* root = pLists->_root;
    Node* tail = pLists->_tail;
    if(root == nullptr) return false;
    while(root != tail) {
        if(root->_ele != tail->_ele) return false;
        root = root->next;
        tail = tail->prev;
    }
    return true;
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
    BList lists;
    for(size_t i = 0; i < N; ++i) {
        int num;
        itr >> num;
        lists.add(num);
    }
    cout << "Is palindrome: " << boolalpha << palindrome(&lists) << endl;
}

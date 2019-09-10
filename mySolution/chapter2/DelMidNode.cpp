#include <iostream>
#include <string>
#include <sstream>
#include "List.h"

using namespace std;

void delMidNode(List* pLists, Node* n)
{
   if(n == nullptr || n->next == nullptr) return;
   Node* cur = n->next;
   n->_ele = cur->_ele;
   n->next = cur->next;
   delete cur;
   cur = nullptr;
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
    cur = cur->next->next;
    delMidNode(&lists, cur);
    cout << "delete the third one: ";
    lists.display();
}

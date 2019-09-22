#include <iostream>
#include <string>
#include <sstream>
#include "List.h"

using namespace std;

Node* loopDetection(Node* head)
{
    if(head == nullptr || head->next == nullptr) return nullptr;
    Node* ns = head;
    Node* nf = head;
    while(ns != nullptr && nf != nullptr) {
        ns = ns->next;
        nf = nf->next->next;
        if(ns == nf) break;
    }
    if(ns != nf) return nullptr;

    ns = head;
    while(ns != nf) {
        ns = ns->next;
        nf = nf->next;
    }
    return ns;
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
    lists._tail->next = lists._root->next->next;
    Node* cur = loopDetection(lists._root);
    cout << "Loop start: ";
    if(cur != nullptr) cout << cur->_ele << endl;
    lists._tail->next = nullptr;
}

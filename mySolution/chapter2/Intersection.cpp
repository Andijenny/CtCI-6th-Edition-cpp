#include <iostream>
#include <string>
#include <sstream>
#include "List.h"

using namespace std;

Node* interaction(Node* n1, Node* n2)
{
    Node* h1 = n1;
    Node* h2 = n2;
    if(h1 == nullptr || h2 == nullptr) return nullptr;
    uint32_t s1 = 0;
    uint32_t s2 = 0;
    while(h1->next != nullptr) {
        h1 = h1->next;
        s1++;
    }
    while(h2->next != nullptr) {
        h2 = h2->next;
        s2++;
    }
    if(h1 != h2) return nullptr;

    if(s1 > s2) {
        uint32_t ds = s1 - s2;
        while(ds > 0) {
            n1 = n1->next;
            ds--;
        }
    }
    else if(s2 > s1) {
        uint32_t ds = s2 - s1;
        while(ds > 0) {
            n2 = n2->next;
            ds--;
        }
    }
    while(n1 != n2) {
        n1 = n1->next;
        n2 = n2->next;
    }
    return n1;
}

int main()
{
    cout << "input N1: ";
    size_t N;
    cin >> N;
    getchar();
    cout << "input list 1: ";
    string str;
    getline(cin, str);
    istringstream itr(str);
    List list1;
    for(size_t i = 0; i < N; ++i) {
        int num;
        itr >> num;
        list1.add(num);
    }

    cout << "input N2: ";
    cin >> N;
    getchar();
    cout << "input list 2: ";
    getline(cin, str);
    itr.clear();
    itr.str(str);
    List list2;
    for(size_t i = 0; i < N; ++i) {
        int num;
        itr >> num;
        list2.add(num);
    }
    Node* head = list1._root;
    Node* prev = head->next->next->next;
    head->next->next = list2._root->next;
    Node* node = interaction(list1._root, list2._root);
    cout << "interaction node: ";
    if(node != nullptr)
        cout << node->_ele << endl;
    head->next->next = prev;
}

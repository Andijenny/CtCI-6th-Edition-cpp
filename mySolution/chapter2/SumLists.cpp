#include <iostream>
#include <string>
#include <sstream>
#include "List.h"

using namespace std;

List sumLists(List* p1, List* p2)
{
    Node* n1 = p1->_root;
    Node* n2 = p2->_root;
    List lists;
    if(n1 == nullptr && n2 == nullptr) return lists;
    int carry = 0;
    while(n1 != nullptr || n2 != nullptr || carry != 0) {
        Node* n = new Node(0);
        n->_ele += carry;
        carry = 0;
        if(n1 != nullptr) {
            n->_ele += n1->_ele;
            n1 = n1->next;
        }
        if(n2 != nullptr) {
            n->_ele += n2->_ele;
            if(n->_ele >= 10) {
                n->_ele = n->_ele%10;
                carry = 1;
            }
            n2 = n2->next;
        }
        lists.add(n);
    }
    return lists;
}


Node* sumListsBigEnd(Node* n1, Node* n2, int& carry)
{
    if(n1 == nullptr && n2 == nullptr) {
        carry = 0;
        return nullptr;
    }
    Node* cur = sumListsBigEnd(n1->next, n2->next, carry);

    Node* n = new Node(0);
    n->_ele = n1->_ele + n2->_ele + carry;
    n->next = cur;

    carry = 0;
    if(n->_ele >= 10) {
        n->_ele = n->_ele%10;
        carry = 1;
    }
    return n;
}

Node* padList(Node* root, int size)
{
    if(size == 0) return root;

    Node* cur = new Node(0);
    cur->next = root;
    return cur;
}

List sumListsBigEnd(List* p1, List* p2)
{
    Node* n1 = p1->_root;
    Node* n2 = p2->_root;

    size_t l1 = p1->size();
    size_t l2 = p2->size();
    if(l1 < l2) {
        n1 = padList(n1, l2-l1);
    }
    else {
        n2 = padList(n2, l1-l2);
    }

    int carry;
    Node* root = sumListsBigEnd(n1, n2, carry);

    if(carry > 0) {
        Node* cur = new Node(carry);
        cur->next = root;
        root = cur;
    }

    List lists;
    while(root != nullptr) {
        lists.add(root);
        root = root->next;
    }
    return lists;
}

int main()
{
    cout << "input n1, n2: ";
    size_t n1, n2;
    cin >> n1 >> n2;
    getchar();
    cout << "input list1: ";
    string str;
    getline(cin, str);
    istringstream itr(str);
    List list1, list2;
    for(size_t i = 0; i < n1; ++i) {
        int num;
        itr >> num;
        list1.add(num);
    }
    cout << "input list2: ";
    getline(cin, str);
    itr.clear();
    itr.str(str);
    for(size_t i = 0; i < n2; ++i) {
        int num;
        itr >> num;
        list2.add(num);
    }
    cout << "summation: ";
  //  List sumList = sumLists(&list1, &list2);
    List sumList = sumListsBigEnd(&list1, &list2);
    sumList.display();
}

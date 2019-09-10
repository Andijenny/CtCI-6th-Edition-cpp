#ifndef LIST_H_
#define LIST_H_
#include <iostream>

struct Node{
    Node* next = nullptr;
    int _ele;
    Node(int ele): _ele(ele)
    {
    }
};

struct List{
    Node* _root = nullptr;
    Node* _tail = nullptr;

    void add(int ele)
    {
        Node* temp = new Node(ele);
        if(_root == nullptr) {
            _root = temp;
            _tail = temp;
            return;
        }
        _tail->next = temp;
        _tail = temp;
    }

    void display()
    {
        Node* n = _root;
        while(n != nullptr) {
            std::cout << n->_ele << "->";
            n = n->next;
        }
        std::cout << "NULL" << std::endl;
    }

    ~List()
    {
        while(_root != nullptr) {
            Node* cur = _root;
            _root = _root->next;
            delete cur;
        }
    }
};


#endif

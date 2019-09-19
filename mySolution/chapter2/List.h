#ifndef LIST_H_
#define LIST_H_
#include <iostream>

struct Node{
    Node* next = nullptr;
    Node* prev = nullptr;
    int _ele;
    Node(int ele): _ele(ele)
    {
    }
};

struct List{
    Node* _root = nullptr;
    Node* _tail = nullptr;
    size_t _size = 0;

    size_t size()
    {
        return _size;
    }
    void add(int ele)
    {
        Node* temp = new Node(ele);
        this->add(temp);
        _size++;
    }

    void add(Node* n)
    {
        if(_root == nullptr) {
            _root = n;
            _tail = n;
            return;
        }
        _tail->next = n;
        _tail = n;
        _size++;
    }

    void add(List* pLists)
    {
        if(_root == nullptr) {
            _root = pLists->_root;
            _tail = pLists->_tail;
        }
        else {
            _tail->next = pLists->_root;
            _tail  = pLists->_tail;
        }
        _size += pLists->_size;
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

struct BList{
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
        temp->prev = _tail;
        _tail = temp;
    }


    void swap(Node* n1, Node* n2) {
        Node* n1p = n1->prev;
        Node* n1n = n1->next;
        n1p->next = n2;
        n1n->prev = n2;
        n2->prev = n1p;
        n2->next = n1n;

        Node* n2p = n2->prev;
        Node* n2n = n2->next;
        n2p->next = n1;
        n2n->prev = n1;
        n1->prev = n2p;
        n1->next = n2n;
    }

    void display()
    {
        Node* n = _root;
        std::cout << "NULL<->";
        while(n != nullptr) {
            std::cout << n->_ele << "<->";
            n = n->next;
        }
        std::cout << "NULL" << std::endl;
    }

    ~BList()
    {
        while(_root != nullptr) {
            Node* cur = _root;
            _root = _root->next;
            delete cur;
        }
    }
};


#endif

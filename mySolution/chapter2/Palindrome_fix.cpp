#include <iostream>
#include <string>
#include <sstream>
#include "List.h"
#include <stack>

using namespace std;

size_t lengthOfList(Node* n)
{
    size_t len = 0;
    while(n != nullptr) {
        len++;
        n = n->next;
    }
    return len;
}

bool palindromeRecursive(Node* head, int len, Node** curNode)
{
    if(len <= 0) {
        (*curNode) = head;
        return true;
    }
    else if(len == 1) {
        *curNode = head->next;
        return true;
    }

    bool isPalindrome = palindromeRecursive(head->next, len-2, curNode);
    if(!isPalindrome || *curNode == nullptr)
        return false;

    if((*curNode)->_ele == head->_ele) {
        *curNode = (*curNode)->next;
        return true;
    }
    return false;
}

template<int N = 0>
bool palindrome(List* pLists)
{
    return false;
}

template<>
bool palindrome<0>(List* pLists)
{
    size_t len = lengthOfList(pLists->_root);
    Node* curNode = new Node(0);
    return palindromeRecursive(pLists->_root, len, &curNode);

}

template<>
bool palindrome<1>(List* pLists)
{
    Node* root = pLists->_root;
    Node* ps = root;
    Node* pf = root;
    stack<int> sk;
    while(pf != nullptr && pf->next != nullptr) {
        sk.push(ps->_ele);
        ps = ps->next;
        pf = pf->next->next;
    }
    if(pf != nullptr) { // odd
        ps = ps->next;
    }
    while(ps != nullptr) {
        if(sk.top() != ps->_ele)
            return false;
        ps = ps->next;
        sk.pop();
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
    List lists;
    for(size_t i = 0; i < N; ++i) {
        int num;
        itr >> num;
        lists.add(num);
    }
    cout << "Is palindrome: " << boolalpha << palindrome<1>(&lists) << endl;
}

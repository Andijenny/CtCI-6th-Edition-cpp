#include <iostream>
#include <string>
#include <sstream>
#include "List.h"

using namespace std;

int kthList(List* pLists, size_t k)
{
   if(pLists == nullptr) return -1;
   Node* cur = pLists->_root;
   Node* kforward = pLists->_root;
   for(size_t i = 0; i < k; ++i) {
       if(kforward == nullptr) return -1;
       kforward = kforward->next;
   }

   while(kforward != nullptr) {
       kforward = kforward->next;
       cur = cur->next;
   }
   return cur->_ele;
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
    cout << "input K: ";
    size_t K;
    cin >> K;
    cout << "k-th to the last: " << kthList(&lists, K) << endl;
}

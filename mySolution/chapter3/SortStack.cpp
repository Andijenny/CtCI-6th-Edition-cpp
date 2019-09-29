#include <iostream>
#include <stack>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

/*O(N^2)*/
template<int N = 0>
void sortStack(stack<int>& s)
{
    stack<int> s2;
    while(!s.empty()) {
        int val = s.top();
        s.pop();
        while(!s2.empty()) {
            if(val >= s2.top()) break;

            s.push(s2.top());
            s2.pop();
        }
        s2.push(val);
    }

    while(!s2.empty()) {
        s.push(s2.top());
        s2.pop();
    }
}

/*quick sort*/
template<>
void sortStack<1>(stack<int>& s)
{
    if(s.empty()) return;
    stack<int> left, right;
    int pivot = s.top();
    s.pop();

    while(!s.empty()) {
        if(pivot < s.top()) {
            left.push(s.top());
            s.pop();
        }
        else {
            right.push(s.top());
            s.pop();
        }
    }

    sortStack<1>(left);
    sortStack<1>(right);

    stack<int> tmp;
    while(!right.empty()) {
        tmp.push(right.top());
        right.pop();
    }
    tmp.push(pivot);
    while(!left.empty()) {
        tmp.push(left.top());
        left.pop();
    }

    while(!tmp.empty()) {
        s.push(tmp.top());
        tmp.pop();
    }
}

/*merge sort*/
template<>
void sortStack<2>(stack<int>& s)
{
    if(s.size() < 2) return;
    stack<int> left, right;

    while(!s.empty()) {
        left.push(s.top());
        s.pop();

        if(s.empty()) continue;

        right.push(s.top());
        s.pop();
    }

    sortStack<2>(left);
    sortStack<2>(right);
    stack<int> tmp;
    while(!left.empty()) {
        int val = left.top();
        while(!right.empty() && val > right.top()) {
            tmp.push(right.top());
            right.pop();
        }
        tmp.push(val);
        left.pop();
    }
    while(!right.empty()) {
        tmp.push(right.top());
        right.pop();
    }
    while(!tmp.empty()) {
        s.push(tmp.top());
        tmp.pop();
    }
}

int main()
{
    cout << "input N: ";
    size_t N;
    cin >> N;
    getchar();
    cout << "push into stack: ";
    string str;
    getline(cin, str);
    istringstream itr(str);
    stack<int> sm;
    for(size_t i = 0; i < N; ++i) {
        int num;
        itr >> num;
        sm.push(num);
    }

    sortStack<2>(sm);
    while(!sm.empty()) {
        cout << sm.top() << " ";
        sm.pop();
    }
    cout << endl;
}

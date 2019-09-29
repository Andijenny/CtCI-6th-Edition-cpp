#include <iostream>
#include <stack>
#include <list>
#include <sstream>

using namespace std;

class StackInPlate
{
public:
    void push(int val)
    {
       m_size++;
       const int indexStack = stackIndex();
       if(m_s.size() <= indexStack)
           m_s.push_back(stack<int>{});
       auto it = m_s.begin();
       advance(it, indexStack);
       it->push(val);
    }
    void pop()
    {
       const int indexStack = stackIndex();
       if(empty()) throw("empty stack");
       auto it = m_s.begin();
       advance(it, indexStack);
       it->pop();
       m_size--;
       if(it->empty())
           m_s.pop_back();
    }
    int top()
    {
       if(empty()) throw("empty stack");
       const int indexStack = stackIndex();
       auto it = m_s.begin();
       advance(it, indexStack);
       return it->top();
    }
    bool empty()
    {
        return m_size == 0;
    }
private:
    const int           SIZE = 4;
    list<stack<int>>    m_s;
    int                 m_size = 0;
    int stackIndex()
    {
        return this->empty() ? -1 : (m_size-1)/SIZE;
    }
};

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
    StackInPlate s1;
    for(size_t i = 0; i < N; ++i) {
        int num;
        itr >> num;
        s1.push(num);
    }
    cout << "stacked values: ";
    while(!s1.empty()) {
        cout << s1.top() << " ";
        s1.pop();
    }
    cout << endl;
}

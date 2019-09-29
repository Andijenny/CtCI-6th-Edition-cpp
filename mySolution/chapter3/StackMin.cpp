#include <iostream>
#include <stack>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;

class NodeMin
{
    public:
        NodeMin(int val, int min)
            :_value(val), _min(min)
        {
        }
        int min() {return _min;}
        int value() {return _value;}

    private:
        int         _value;
        int         _min;
};

class StackMin
{
    public:
        StackMin()
        {
        }
        void push(int val)
        {
            m_s.push(NodeMin(val, min(val)));
        }
        void pop()
        {
            m_s.pop();
        }
        int top()
        {
            return m_s.top().value();
        }
        int min() {
            if(m_s.empty()) 
                return numeric_limits<int>::max();
            return m_s.top().min();
        }
        bool empty() {return m_s.empty();}
    private:
        stack<NodeMin>      m_s;

        int min(int val)
        {
            return std::min(val, this->min());
        }
};

class StackMin2
{
    public:
        StackMin2()
        {
        }
        void push(int val)
        {
            m_s.push(val);
            this->pushMin(val);
        }
        void pop()
        {
            if(m_s.top() <= m_s2.top())
                m_s2.pop();
            m_s.pop();
        }
        int top()
        {
            return m_s.top();
        }
        int min() {
            return m_s2.top();
        }
        bool empty() {return m_s.empty();}
    private:
        stack<int>      m_s;
        stack<int>      m_s2;

        void pushMin(int val)
        {
            if(m_s2.empty() || val <= m_s2.top()) {
                m_s2.push(val);
            }
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
    StackMin2 sm;
    for(size_t i = 0; i < N; ++i) {
        int num;
        itr >> num;
        sm.push(num);
    }
    while(!sm.empty()) {
        cout << sm.min() << " ";
        sm.pop();
    }
    cout << endl;
}

#include <iostream>
#include <stack>
#include <sstream>

using namespace std;
class MyQueue {
public:
    void enqueue(int val)
    {
        ms1.push(val);
    }
    int dequeue()
    {
        shift();
        int val = ms2.top();
        ms2.pop();
        return val;
    }
    bool empty()
    {
        return ms1.empty() && ms2.empty();
    }
    void shift()
    {
        if(ms2.empty()) {
            while(!ms1.empty()) {
                ms2.push(ms1.top());
                ms1.pop();
            }
        }
    }
private:
    stack<int> ms1, ms2;
};

int main()
{
    cout << "input N: ";
    size_t N;
    cin >> N;
    getchar();
    cout << "push into queue: ";
    string str;
    getline(cin, str);
    istringstream itr(str);
    MyQueue s1;
    for(size_t i = 0; i < N; ++i) {
        int num;
        itr >> num;
        s1.enqueue(num);
    }
    cout << "stacked values: ";
    while(!s1.empty()) {
        cout << s1.dequeue() << " ";
    }
    cout << endl;
}

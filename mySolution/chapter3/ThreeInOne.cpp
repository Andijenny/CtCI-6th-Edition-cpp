#include <iostream>
#include <vector>

using namespace std;

class MultiStack {
    public:
        MultiStack(size_t stackSize)
            : _stackCapacity(stackSize)
        {
            _size.resize(SIZE);
            _values.resize(SIZE * stackSize);
        }
        void push(size_t stackNum, int digital)
        {
            if(isFull(stackNum)) throw("no space");
            _size[stackNum]++;
            _values[topIndex(stackNum)] = digital;
        }
        void pop(size_t stackNum)
        {
            if(empty(stackNum)) throw("empty stack");

            _size[stackNum]--;

        }
        int top(size_t stackNum)
        {
            return _values[topIndex(stackNum)];
        }
    private:
        bool isFull(size_t stackNum)
        {
            return _size[stackNum] == _stackCapacity;
        }
        bool empty(size_t stackNum)
        {
            return _size[stackNum] == 0;
        }
        size_t topIndex(size_t stackNum)
        {
            return _size[stackNum] + stackNum*_stackCapacity - 1;
        }
    private:
        const size_t    SIZE = 3;
        size_t          _stackCapacity;
        vector<size_t>  _size;
        vector<int>     _values;
};

int main()
{
    MultiStack msk(10);
}

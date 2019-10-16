#include <cstdlib>
#include <ctime>
#include <numeric>
#include <algorithm>
#include "tree.hpp"

using namespace std;

template<typename T>
class RandomNode{
public:
    using NodePtr = shared_ptr<RandomNode>;
    RandomNode(T v) : _data(v), _size(1)
    {
    }
    template<typename U>
    void setLeftChild(U&& ptr)
    {
        _childs[0] = forward<U>(ptr);
    }

    template<typename U>
    void setRightChild(U&& ptr)
    {
        _childs[1] = forward<U>(ptr);
    }

    template<typename U>
    void setParent(U&& ptr)
    {
        _parent = forward<U>(ptr);
    }
    const NodePtr& getLeft() const
    {
        return _childs[0];
    }
    const NodePtr& getRight() const
    {
        return _childs[1];
    }
    NodePtr getParent() const
    {
        auto sp = _parent.lock();
        return sp;
    }
    const T& getValue() {return _data;}
private:
    void add(const NodePtr& parent, const T& v)
    {
        const int8_t ic = v > _data ? 1 : 0;
        if(!_childs[ic]) {
            _childs[ic] = make_shared<RandomNode<T>>(v);
            _childs[ic]->setParent(parent);
        }
        else {
            _childs[ic]->add(_childs[ic], v);
        }
        _size++;
    }

    bool isLeftBranch()
    {
        if(!this->getParent()) return false;
        if(this->getParent()->getLeft().get() == this)
            return true;
        return false;
    }
    bool hasNoChild()
    {
        return !_childs[0] && !_childs[1];
    }
    NodePtr getRandomNode(const NodePtr& cur)
    {
        return get(cur, rand() % _size + 1);
    }

    NodePtr get(const NodePtr& cur, size_t n)
    {
        if(n == _size)
            return cur;
        if(_childs[0] && n <= _childs[0]->_size)
            return _childs[0]->get(_childs[0], n);
        else
            return _childs[1]->get(_childs[1], n - (_childs[0] ? _childs[0]->_size : 0));
    }

    void replace(const NodePtr& newNode)
    {
        if(this->getParent()) {
            if(this->getParent()->getLeft().get() == this)
                this->getParent()->setLeftChild(newNode);
            else
                this->getParent()->setRightChild(newNode);
        }
        if(newNode) {
            if(this->getLeft() != newNode) {
                newNode->setLeftChild(this->getLeft());
                if(this->getLeft())
                    this->getLeft()->setParent(newNode);
                this->setLeftChild(NodePtr());
            }

            if(this->getRight() != newNode) {
                newNode->setRightChild(this->getRight());
                if(this->getRight()) {
                    this->getRight()->setParent(newNode);
                }
                this->setRightChild(NodePtr());
            }
           // else {
           //     cout << "new par " << newNode->getValue() << endl;
           //     if(this->getLeft()) {
           //         this->setLeftChild(NodePtr());
           //         cout << "here ?" << endl;
           //     }
           //     cout << "here ?" << endl;
           //    // else
           //    //     this->setRightChild(NodePtr());
           // }
            newNode->setParent(this->getParent());
        }
       // this->setParent(NodePtr());
       cout << "aa" << endl;
    }

    NodePtr replaceWithLRChild()
    {
        if(!_childs[0] && !_childs[1]) {
            NodePtr n = NodePtr();
            this->replace(n);
            return n;
        }
        if(_childs[0]) {
            NodePtr r = _childs[0];
            while(r->getRight()) {
                r = r->getRight();
            }
            if(r->getLeft()) {
                cout << "r " << r->_data << endl;
                r->replace(r->getLeft());
            }
            this->replace(r);
            return r;
        }
        else {
            NodePtr l = _childs[1];
            while(l->getLeft()) {
                l = l->getLeft();
            }
            if(l->getRight()){
                l->replace(l->getRight());
            }
            this->replace(l);
            return l;
        }
        return NodePtr();
    }
private:
    T                           _data;
    array<NodePtr, 2>           _childs;
    weak_ptr<RandomNode>        _parent;
    size_t                      _size{1};

    template<typename U> friend class RandomTree;
};

template<typename T>
class RandomTree : public tree<T, RandomNode>
{
    using NodePtr = typename tree<T, RandomNode>::NodePtr;
    using tree<T, RandomNode>::tree;
public:
    void insert(const T& v)
    {
        if(!this->m_root) {
            this->m_root = make_shared<RandomNode<T>>(v);
            return;
        }
        this->m_root->add(this->m_root, v);
    }

    NodePtr getRandomNode()
    {
        if(!this->m_root) return shared_ptr<RandomNode<T>>();
        //srand(time(NULL));
        return this->m_root->getRandomNode(this->m_root);
    }

    void deletion(const T& v)
    {
        NodePtr curNode = find(this->m_root, v);
        if(curNode->hasNoChild()) {
            if(curNode == this->m_root) {
                this->m_root = NodePtr();
            }
            else {
                if(curNode->isLeftBranch())
                    curNode->getParent()->setLeftChild(NodePtr());
                else
                    curNode->getParent()->setRightChild(NodePtr());
            }
        }
        else if(!curNode->getLeft() || !curNode->getRight()) {
            NodePtr n = curNode->getLeft() ? curNode->getLeft() : curNode->getRight();
            if(curNode == this->m_root) {
                this->m_root = n;
            }
            else {
                if(curNode->isLeftBranch())
                    curNode->getParent()->setLeftChild(n);
                else
                    curNode->getParent()->setRightChild(n);
            }
        }
        else {
            NodePtr l = curNode->getLeft();
            while(l->getRight()) {
                l = l->getRight();
            }
            NodePtr tmp = l;
            if(!l->getLeft()) {
                if(l->isLeftBranch())
                    tmp->getParent()->setLeftChild(NodePtr()); // use tmp to keep l temporarily
                else
                    tmp->getParent()->setRightChild(NodePtr());
            } 
            else {
                if(l->getParent() != curNode) {
                    if(l->isLeftBranch())
                        tmp->getParent()->setLeftChild(l->getLeft());
                    else
                        tmp->getParent()->setRightChild(l->getLeft());
                }
            }
            if(l->getParent() != curNode) {
                l->setLeftChild(curNode->getLeft());
                l->getLeft()->setParent(l);
            }
            l->setRightChild(curNode->getRight());
            l->getRight()->setParent(l);
            if(curNode == this->m_root) {
                this->m_root = l;
                this->m_root->setParent(NodePtr());
            }
            else {
                l->setParent(curNode->getParent());
                if(curNode->isLeftBranch())
                    curNode->getParent()->setLeftChild(l);
                else
                    curNode->getParent()->setRightChild(l);
            }
        }
    }

private:
    NodePtr find(const NodePtr& cur, const T& v)
    {
        if(!cur) return shared_ptr<RandomNode<T>>();
        if(v == cur->getValue()) return cur;
        if(v <= cur->getValue())
            return this->find(cur->getLeft(), v);
        else
            return this->find(cur->getRight(), v);

        return shared_ptr<RandomNode<T>>();
    }
};

int main()
{
    vector<int> vec(8);
    srand(time(0));
    iota(vec.begin(), vec.end(), 0);
    random_shuffle(vec.begin(), vec.end(), [](int i){return rand() % i;});
    //initializer_list<int> vec{6, 3, 1, 0, 2, 5, 4, 7};
    //initializer_list<int> vec{3, 2, 1, 0, 6, 5, 4, 7};
    //initializer_list<int> vec{2,1,0,6,4,3,5,7};
    for(auto i : vec)
    cout << i << " ";
    cout << endl;
    RandomTree<int> tree;
    for(auto it = vec.begin(); it != vec.end(); ++it) {
        tree.insert(*it);
    }
    tree.print2D();
    vector<int> cc(8);
    for(uint32_t i = 0; i < 10000; ++i) {
        cc[tree.getRandomNode()->getValue()]++;
    }
    cout << "frequency for each node: ";
    for(auto i : cc)
        cout << i << " ";
    cout << endl;
    tree.deletion(6);
    cout << "after delete 6" << endl;
    tree.print2D();
}

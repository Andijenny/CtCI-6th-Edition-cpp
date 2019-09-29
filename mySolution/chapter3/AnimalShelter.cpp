#include <iostream>
#include <list>
#include <string>
#include <sstream>

using namespace std;

enum class ANIMAL : int {
    OTHERS = -1,
    CAT,
    DOG
};


class Animal {
public:
    Animal(string name):
        _name(name)
    {
    }
    virtual ~Animal()
    {
    }
    virtual ANIMAL getCategory() {
        return ANIMAL::OTHERS;
    }
    string name() {return _name;}
    void setOrder(int order)
    {
        _order = order;
    }
    int getOrder() {return _order;}

    bool isOrderthan(Animal* a) {
        return this->_order < a->_order;
    }
private:
    string  _name;
    int     _order;
};

class Dog : public Animal {
    using Animal::Animal;
    ANIMAL getCategory() override
    {
        return ANIMAL::DOG;
    }
};

class Cat : public Animal {
    using Animal::Animal;
    ANIMAL getCategory() override
    {
        return ANIMAL::CAT;
    }
};

class ShelterQueue {
public:
   void enqueue(Animal* a)
   {
       a->setOrder(m_size++);
       if(a->getCategory() == ANIMAL::CAT) {
           m_cats.push_back(a);
       }
       else if(a->getCategory() == ANIMAL::DOG) {
           m_dogs.push_back(a);
       }
   }

   Animal* dequeueAny()
   {
       if(m_cats.empty() && m_dogs.empty()) return nullptr;

       if(m_cats.empty()) {
           return dequeueDog();
       }
       else if(m_dogs.empty()) {
           return dequeueCat();
       }

       Animal* dog = m_dogs.front();
       Animal* cat = m_cats.front();
       if(cat->isOrderthan(dog)) {
           return dequeueCat();
       }
       else {
           return dequeueDog();
       }
   }

   Animal* dequeueDog()
   {
       if(m_dogs.empty()) throw("empty stack");

       Animal* a = m_dogs.front();
       m_dogs.pop_front();
       return a;
   }

   Animal* dequeueCat()
   {
       if(m_cats.empty()) throw("empty stack");

       Animal* a = m_cats.front();
       m_cats.pop_front();
       return a;
   }

   bool empty()
   {
        return m_cats.empty() && m_dogs.empty();
   }
private:
   list<Animal*>    m_cats;
   list<Animal*>    m_dogs;
   size_t          m_size = 0;
};

int main()
{
    Animal* a1 = new Dog("happy");
    Animal* a2 = new Dog("sad");
    Animal* a3 = new Cat("tough");
    Animal* a4 = new Cat("exciting");

    ShelterQueue animals;
    animals.enqueue(a1);
    animals.enqueue(a3);
    animals.enqueue(a2);
    animals.enqueue(a4);

    while(!animals.empty()) {
        Animal* a = animals.dequeueAny();
        cout << "adopt " << static_cast<int>(a->getCategory()) << " : " << a->name() << endl;
        delete a;
    }
}

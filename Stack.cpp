#include <string.h>
#include <iostream>
#include <vector>

template <class Type>
class Element
{
public:
    Type value;
    Element<Type> *next;

    Element()
    {
        this->next = nullptr;
    }

    Element(Type v) : value(v)
    {
        this->next = nullptr;
    }
};

template<class Type>
class Container{
public:
    std::size_t size;
    Element<Type>* front;
    Element<Type>* end;


    virtual void push_front(Type element) = 0;
    virtual Type pop_front() = 0;

    bool empty(){
        return bool(size);
    }
};


template <class Type>
class Stack : public Container<Type>
{
public:
    Stack()
    {
        this->front = nullptr;
        this->size = 0;
    }

    Stack(std::initializer_list<Type> init)
    {
        this->front = nullptr;
        for (auto it = std::rbegin(init); it != std::rend(init); it++)
        {
            this->push_front(*it);
        }
    }

    void push_front(Type value) final
    {

        Element<Type> *tmp = new Element<Type>(value);
        tmp->next = this->front;
        this->front = tmp;
        this->size++;
    }

    Type pop_front() final
    {
        Element<Type> *tmp = this->front;
        this->front = this->front->next;
        Type result = tmp->value;
        delete tmp;
        this->size--;
        return result;
    }
};

template <class Type>
class List : public Container<Type>
{
//Type operator[](std::size_t index);
public:
    List()
    {
        this->front = nullptr;
        this->size = 0;
    }

    List(std::initializer_list<Type> init)
    {
        this->front = nullptr;
        for (auto it = std::rbegin(init); it != std::rend(init); it++)
        {
            this->push_front(*it);
        }
    }

    void push_front(Type value) final
    {

        Element<Type> *tmp = new Element<Type>(value);
        tmp->next = this->front;
        this->front = tmp;
        this->size++;
    }

    Type pop_front() final
    {
        Element<Type> *tmp = this->front;
        this->front = this->front->next;
        Type result = tmp->value;
        delete tmp;
        this->size--;
        return result;
    }

    void insert(Type value, std::size_t index)
    {
        Type tmp[index];
        for (int i=0;i<index;i++)
        {
            tmp[i]=pop_front();
        }
        push_front(value);
        for (int i=index;i>0;i--)
        {
            push_front(tmp[i]);
        }
    }
};

template <class Type>
class HashTable : public Container<Type>
{

public:
    std:vector<List> table;

    HashTable(int size)
    {
        table= new Element<Type>*[size];
        for ( int i = 0; i < size; i++ ) 
        {
            table[i] = NULL;
        }
        
    }

    void push_front(Type value) final
    {
        Type i=value % size;
        Element<Type> *tmp = new Element<Type>(value);
        tmp->next = table[i]->front;
        table[i]->front = tmp;
        
    }

    Type pop_front(Type value) final
    {
        Type i = value % size;
        Element<Type> *tmp = table[i]->front;
        table[i]->front = table[i]->front->next;
        Type result = tmp->value;
        delete tmp;
        return result;
    }

};

int main()
{
    Stack<int> S = {1,2,3,4,5};
    std::cout << S.pop_front() << std::endl;

    List<int> L = {1,2,3,4,5};
    L.insert(6,2);
    std::cout << L.pop_front() << std::endl;

}

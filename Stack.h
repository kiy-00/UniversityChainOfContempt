#pragma once
#include<iostream> 
#include"LinkNode.h"
using namespace std;


const int StackDefaultSize = 100;

template<class T>
class Stack
{
private:
    LinkNode<T>* top;
public:
    Stack() :top(NULL) {};
    ~Stack()
    {
        makeEmpty();
        delete top;
    }
    Stack(const Stack<T>& s);

    Stack<T>& operator=(const Stack<T>& s);

    void makeEmpty();

    void Push(const T& x);

    bool Pop();

    bool isEmpty()const
    {
        return top == NULL;
    }
    T getTop()
    {
        return top->getData();
    }
    int getSize()const;

    Stack<T> reverse()const;

    void output()const;

};
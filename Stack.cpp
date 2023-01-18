#include"Stack.h"

template<class T>
Stack<T>::Stack(const Stack<T>& s)
{
    top = NULL;
    makeEmpty();

    T memory[10 * StackDefaultSize];
    int cnt = -1;
    LinkNode<T>* p = s.top;
    while (p != NULL)
    {
        memory[++cnt] = p->getData();
        p = p->link;
    }
    for (int i = cnt; i >= 0; i--)
    {
        Push(memory[i]);
    }
}

template<class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& s)
{
    makeEmpty();

    T memory[10 * StackDefaultSize];
    int cnt = -1;
    LinkNode<T>* p = s.top;
    while (p != NULL)
    {
        memory[++cnt] = p->getData();
        p = p->link;
    }
    for (int i = cnt; i >= 0; i--)
    {
        Push(memory[i]);
    }
    return *this;
}


template<class T>
void Stack<T>::makeEmpty()
{
    LinkNode<T>* p;
    while (top != NULL)
    {
        p = top;
        top = top->link;
        delete p;
    }
}

template<class T>
void Stack<T>::Push(const T& x)
{
    top = new LinkNode<T>(x, top);
    if (top == NULL)
    {
        cerr << "Allocation Error!\n";
        exit(1);
    }
}

template<class T>
bool Stack<T>::Pop()
{
    if (isEmpty())
    {
        return false;
    }
    LinkNode<T>* p = top;
    top = top->link;

    delete p;
    return true;
}

template<class T>
int Stack<T>::getSize()const
{
    int k = 0;
    LinkNode<T>* p = top;
    while (p != NULL)
    {
        k++;
        p = p->link;
    }
    return k;
}

template<class T>
Stack<T> Stack<T>::reverse()const
{
    Stack<T> s;
    LinkNode<T>* p = top;
    while (p != NULL)
    {
        s.Push(p->getData());
        p = p->link;
    }
    return s;
}

template<class T>
void  Stack<T>::output()const
{
    LinkNode<T>* p = top;
    while (p != NULL)
    {
        cout << p->getData();
        p = p->link;
        if (p != NULL)
        {
            cout << " ";
        }
    }
}

 
#include"LinkedQueue.h"
template<class T>
LinkedQueue<T>::LinkedQueue()
{
	first=new LinkNode<T>;
	front = rear = NULL;
}

template<class T>
LinkedQueue<T>::~LinkedQueue()
{
	makeEmpty();
	delete first;
}

template<class T>
void LinkedQueue<T>::makeEmpty()
{
	LinkNode<T>* current;
	while (first->link != NULL)
	{
		current = first->link;
		first->link = current->link;
		delete current;
	}
}

template<class T>
bool LinkedQueue<T>::EnQueue(const T  x)
{
	LinkNode<T>* current = new LinkNode<T>(x);
	if (current == NULL)
	{
		//
		return false;
	}
	if (front == NULL)
	{
		front=rear= current;
		first->link = front;
		return true;
	}
	rear->link = current;
	rear = current;
	return true;
}

template<class T>
void LinkedQueue<T>::DeQueue()
{
	LinkNode<T>* p = front;
	front = front->link;
	first->link = front;
	delete p;
}
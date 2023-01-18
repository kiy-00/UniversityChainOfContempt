#pragma once
#include<iostream>
#include"LinkNode.h"
using namespace std;

template<class T>
class LinkedQueue
{
private:
	LinkNode<T>* first, * front, * rear;
public:
	LinkedQueue();

	~LinkedQueue();

	void makeEmpty();

	bool isEmpty()
	{
		return first->link == NULL;
	}

	bool EnQueue(const T x);

	T Front()
	{
		return front->getData();
	}

	void DeQueue();
};

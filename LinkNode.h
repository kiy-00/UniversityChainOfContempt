#pragma once
#include<iostream>
template<class T>
class LinkNode
{
private:
	T data;

public:
	LinkNode<T>* link;
	//已知Link初始化LinkNode
	LinkNode(LinkNode<T>* ptr = NULL)
	{
		link = ptr;
	}
	//已知data Link 初始化LinkNode
	LinkNode(const T& item, LinkNode<T>* ptr = NULL)
	{
		data = item;
		link = ptr;
	}
	//得到LinkNode的Data
	T getData()
	{
		return data;
	}
	//设置LinkNode的Data
	void setData(const T& item)
	{
		data = item;
	}

};

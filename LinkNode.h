#pragma once
#include<iostream>
template<class T>
class LinkNode
{
private:
	T data;

public:
	LinkNode<T>* link;
	//��֪Link��ʼ��LinkNode
	LinkNode(LinkNode<T>* ptr = NULL)
	{
		link = ptr;
	}
	//��֪data Link ��ʼ��LinkNode
	LinkNode(const T& item, LinkNode<T>* ptr = NULL)
	{
		data = item;
		link = ptr;
	}
	//�õ�LinkNode��Data
	T getData()
	{
		return data;
	}
	//����LinkNode��Data
	void setData(const T& item)
	{
		data = item;
	}

};

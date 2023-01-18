#pragma once
#include<iostream>
using namespace std;

template<class T>
class AVLNode
{
public:
	AVLNode<T>* left, * right;
	int bf;//balance factor ÓÒ¼õ×ó
	T data;
public:
	AVLNode() :left(NULL), right(NULL), bf(0) {};

	AVLNode(T d, AVLNode<T>* l = NULL, AVLNode<T>* r = NULL)
	{
		data = d;
		left = l;
		right = r;
		bf = 0;
	}
};


template<class T>
class AVLTree
{
private:

	AVLNode<T>* root;
	void RotateL(AVLNode<T>* tree, AVLNode<T>*& newtree);
	void RotateR(AVLNode<T>* tree, AVLNode<T>*& newtree);

	void leftBalance(AVLNode<T>*& tree, int& taller);
	void rightBalance(AVLNode<T>*& tree, int& taller);

	int insert(AVLNode<T>*& tree, T x, int& taller);
	int find(AVLNode<T>* tree, T& x, AVLNode<T>*& ptr);

	void makeEmpty(AVLNode<T>* tree);
public:
	AVLTree() :root(NULL) {};
	~AVLTree()
	{
		makeEmpty(root);
	}
	int insert(T  x)
	{
		int n = 0;  
		return insert(this->root, x, n);
	};
	int find(T& x, AVLNode<T>*& ptr)
	{
		return find(root, x, ptr);
	}
};
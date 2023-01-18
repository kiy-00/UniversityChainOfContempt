#include"AVLTree.h"

template<class T>
void AVLTree<T>::RotateL(AVLNode<T>* tree, AVLNode<T>*& newtree)
{
	newtree = tree->right;
	tree->right = newtree->left;
	newtree->left = tree;
}

template<class T>
void AVLTree<T>::RotateR(AVLNode<T>* tree, AVLNode<T>*& newtree)
{
	newtree = tree->left;
	tree->left = newtree->right;
	newtree->right = tree;
}

template<class T>
void AVLTree<T>::leftBalance(AVLNode<T>*& tree, int& taller)
{
	AVLNode<T>* leftsub = tree->left, * rightsub;
	switch (leftsub->bf)
	{
		case -1:
			tree->bf = leftsub->bf = 0;
			RotateR(tree, tree);
			taller = 0;
			break;
		case 0:
			break;
		case 1:
			rightsub = leftsub->right;
			switch (rightsub->bf)
			{
				case -1:
					tree->bf = 1;
					leftsub->bf = 0;
					break;
				case 0:
					tree->bf = 0;
					leftsub->bf = 0;
					break;
				case 1:
					tree->bf = 0;
					leftsub->bf = -1;
					break;
			}
			rightsub->bf = 0;
			RotateL(leftsub, tree->left);
			RotateR(tree, tree);
			taller = 0;
	}
}

template<class T>
void AVLTree<T>::rightBalance(AVLNode<T>*& tree, int& taller)
{
	AVLNode<T>* rightsub = tree->right, * leftsub;
	switch (rightsub->bf)
	{
		case 1:
			tree->bf = rightsub->bf = 0;
			taller = 0;
			RotateL(tree, tree);
			taller = 0;
			break;
		case 0:
			break;
		case -1:
			leftsub = rightsub->left;
			switch (leftsub->bf)
			{
				case -1:
					tree->bf = 0;
					rightsub->bf = 1;
					break;
				case 0:
					tree->bf = 0;
					rightsub->bf = 0;
					break;
				case 1:
					tree->bf = -1;
					rightsub->bf = 0;
					break;
			}
			rightsub->bf = 0;
			RotateR(rightsub, tree->right);
			RotateL(tree, tree);
			taller = 0;
	}
}

template<class T>
int AVLTree<T>::insert(AVLNode<T>*& tree, T  x, int& taller)
{
	int success = 0;  
	if (tree == NULL)
	{
		tree = new AVLNode<T>(x);  
		success = (tree != NULL) ? 1 : 0;
		if (success)
		{
			taller = 1;
		}
	}
	else if (x < tree->data)
	{
		success = insert(tree->left, x, taller);
		if (taller)
		{
			switch (tree->bf)
			{
				case -1:
					leftBalance(tree, taller);
					break;
				case 0:
					tree->bf = -1;
					break;
				case 1:
					tree->bf = 0;
					taller = 0;
					break;
			}
		}
	}
	else if (x > tree->data)
	{
		success = insert(tree->right, x, taller);
		if (taller)
		{
			switch (tree->bf)
			{
				case 1:
					rightBalance(tree, taller);
					break;
				case 0:
					tree->bf = 1;
					break;
				case -1:
					tree->bf = 0;
					taller = 0;
					break;
			}
		}
	}
	return success;
}

template<class T>
int AVLTree<T>::find(AVLNode<T>* tree, T& x, AVLNode<T>*& ptr)
{
	if (tree == NULL)
	{
		ptr = NULL;
		return 0;
	}
	if (tree->data == x)
	{
		//cout << tree->data << endl; cout << "zhaodaola" << endl;
		ptr = tree;
		return 1;
	}
	if (x<tree->data)
	{
		//cout << tree->data << endl;
		return find(tree->left, x, ptr);
	}
	else
	{
		//cout << tree->data << endl;
		return find(tree->right, x, ptr);
	}
}


template<class T>
void AVLTree<T>::makeEmpty(AVLNode<T>* tree)
{
	if (tree == NULL)
	{
		return;
	}
	makeEmpty(tree->left);
	makeEmpty(tree->right);
	delete tree;
}
#pragma once
const int UFSetsDefaultSize = 10;

class UFsets
{
public:
	UFsets(int sz = UFSetsDefaultSize);
	~UFsets()
	{
		delete[]parent;
	}
	void Union(int root1, int root2)
	{
		root1 = CollapsingFind(root1);
		root2 = CollapsingFind(root2);
		parent[root1] += parent[root2];
		parent[root2] = root1;
	}
	int Find(int x)
	{
		while (parent[x] >= 0)
		{
			x = parent[x];
		}
		return x;
	}
	int CollapsingFind(int x);
	void WeightedUnion(int roo1, int root2);
private:
	int* parent;
	int size;
};
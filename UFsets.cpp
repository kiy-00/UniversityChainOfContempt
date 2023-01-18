#include"UFsets.h"
#include"iostream"
UFsets::UFsets(int sz)
{
	size = sz;
	parent = new int[size];
	for (int i = 0; i < size; i++)
	{
		parent[i] = -1;
	}
}

void UFsets::WeightedUnion(int root1, int root2)
{
	if (parent[root1] < parent[root2])
	{
		Union(root1, root2);
	}
	else
	{
		Union(root2, root1);
	}
}

int UFsets::CollapsingFind(int x)
{
	int i;

	for (i = x; parent[i] >= 0; i = parent[i]);
	while (x != i)
	{
		int temp = parent[x];
		parent[x] = i;
		x = temp;
	}
	return i;
}
 
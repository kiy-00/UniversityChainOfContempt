#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include"String.h"
#include"Graph.cpp"
#include"AVLTree.cpp"
#include<iomanip>

const int RANKINGNUM = 3;
const int UNINUM = 2000;

template<class T, class E>
void ttarjan(Graphlnk<T, E>& G, UFsets& U, Stack<int>& S, int x, int dfn[], int low[], int instack[], int  timer);

/*求强连通分量*/
template<class T, class E>
void tarjan(Graphlnk<T, E>& G, UFsets& U);


class Uni
{
	friend class UCC;
private:
	String m_name;
	int m_rank[RANKINGNUM];
public:
	Uni(String s = "")
	{
		m_name = s;
		for (int i = 0; i < RANKINGNUM; i++)
		{
			m_rank[i] = 0;
		}
	}
	Uni(const Uni& u)
	{
		this->m_name = u.m_name;
		for (int i = 0; i < RANKINGNUM; i++)
		{
			this->m_rank[i] = u.m_rank[i];
		}
	}
	Uni& operator=(Uni& u)
	{
		this->m_name = u.m_name;
		for (int i = 0; i < RANKINGNUM; i++)
		{
			this->m_rank[i] = u.m_rank[i];
		}
		return *this;
	}
	bool operator>(Uni& u)
	{
		return this->m_name > u.m_name;
	}
	bool operator<(Uni& u)
	{
		return this->m_name < u.m_name;
	}
	bool operator==(Uni& u)
	{
		return this->m_name == u.m_name;
	}
	void setrank(int ranklist, int ranking)
	{
		m_rank[ranklist] = ranking;
	}
	void merge(Uni u)
	{
		for (int i = 0; i < RANKINGNUM; i++)
		{
			this->m_rank[i] += u.m_rank[i];
		}
	}
};

class UCC
{
private:
	/*记录大学连通的图*/
	Graphlnk<String, int> UniGraph;
	/*记录在同一个强连通分量中的并查集*/
	UFsets UniSet;
	/*强连通分量的重建图，以并查集中的族长在大学连通图中的下标为图中顶点*/
	Graphlnk<int, int> StrongConComGraph;
	/*记录大学信息的AVL搜索树*/
	AVLTree<Uni> UniTree;
	/*排行榜的名字*/
	String RankingName[RANKINGNUM];
	/*大学名最大长度，用于定义字符串，并在输出时对齐*/
	int UniNameLength;
	/*排行榜名最大长度，用于定义字符串，并在输出时对齐*/
	int RankingNameLength;
public:
	UCC();
	void UCCask();
	void findchain(int& highPlace, int& lowPlace);
};
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

/*��ǿ��ͨ����*/
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
	/*��¼��ѧ��ͨ��ͼ*/
	Graphlnk<String, int> UniGraph;
	/*��¼��ͬһ��ǿ��ͨ�����еĲ��鼯*/
	UFsets UniSet;
	/*ǿ��ͨ�������ؽ�ͼ���Բ��鼯�е��峤�ڴ�ѧ��ͨͼ�е��±�Ϊͼ�ж���*/
	Graphlnk<int, int> StrongConComGraph;
	/*��¼��ѧ��Ϣ��AVL������*/
	AVLTree<Uni> UniTree;
	/*���а������*/
	String RankingName[RANKINGNUM];
	/*��ѧ����󳤶ȣ����ڶ����ַ������������ʱ����*/
	int UniNameLength;
	/*���а�����󳤶ȣ����ڶ����ַ������������ʱ����*/
	int RankingNameLength;
public:
	UCC();
	void UCCask();
	void findchain(int& highPlace, int& lowPlace);
};
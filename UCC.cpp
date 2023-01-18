#include"UCC.h"
/*
ARWU
Times
QS
*/

UCC::UCC():UniGraph(UNINUM),UniSet(UNINUM),UniTree(), StrongConComGraph(UNINUM)
{
	UniNameLength=25;
    RankingNameLength=5;
	for (int i = 0; i < RANKINGNUM; i++)
	{
		cout << "�������" << i + 1 << "����ѧ���а���" << endl;
		String sranking;
		cin >> sranking;
		RankingName[i] = sranking;
		cout << "�밴˳�������ѧ����(��Сд������),-1����"<<endl;
		
		int tag = 0;//�Ƿ������а�ڶ����Ժ�Ĵ�ѧ
		int cnt = 0;
		String pre(UniNameLength), cur(UniNameLength);
		while (1)
		{
			cnt++;
			cout << "��" << cnt << "����ѧ:";
			cin >> cur; 
			cur.strlwr();//��ѧ����ת��ΪСд����Сд������
			if (cur == "-1")
			{
				break;
			}
			Uni u = Uni(cur); //ʹ�ô�ѧ������Uni����
			u.setrank(i, cnt);  //���ô�ѧ�ڱ������а��ϵ�����
			AVLNode<Uni>* ptr; 
			int  exist = UniTree.find(u,ptr);  //Ѱ�Ҹô�ѧ�����������Ƿ��Ѵ���
			 
			if (!exist)//�����ڣ������������ʹ�ѧ��ͨͼ
			{
				UniTree.insert(u); 
				UniGraph.insertVertex(cur); 
			}
			else//���ڣ������������ص�ָ��ָ�����ݺϲ�������¼����
			{
				ptr->data.merge(u);  
			}
			if (tag)//��ǰһ����ѧ�ڴ�ѧ��ͨͼ�Ͻ������
			{
				int s = UniGraph.getVertexPos(pre);  
				int t = UniGraph.getVertexPos(cur);   
				UniGraph.insertEdge(s,t,i);   
			}
			tag = 1; 
			pre = cur;  
		}
	}

	tarjan(UniGraph, UniSet); //��ǿ��ͨ����

	//����ԭ���Ĵ�ѧ��ͨͼ��Ϊ�����ǿ��ͨ����������ͼ
	int numofvertices = UniGraph.NumberOfVertices();
	for (int i = 0; i < numofvertices; i++)
	{
		int from = UniSet.CollapsingFind(i); 
		StrongConComGraph.insertVertex(from);
		int frompoint = StrongConComGraph.getVertexPos(from);
		int j = UniGraph.getFirstNeighbor(i);
		while (1)
		{
			if (j == -1)
			{
				break;
			}
			int toward= UniSet.CollapsingFind(j); 
			 
			StrongConComGraph.insertVertex(toward); 
			int towardpoint = StrongConComGraph.getVertexPos(toward);
			if (from != toward)
			{
				StrongConComGraph.insertEdge(frompoint, towardpoint, 1);
			}
			j = UniGraph.getNextNeighbor(i, j);
		}
	}

}

void UCC::UCCask()
{
	while (getchar() != '\n');
	cout << "��������Ĵ�ѧ��"<<endl;
	String highUni;
	AVLNode<Uni>* highUniPtr;
	cin >> highUni;
	Uni highTemp = Uni(highUni);
	int highExist =UniTree.find(highTemp, highUniPtr);
	 
	cout << "������Է���ѧУ��" << endl;
	String lowUni;
	AVLNode<Uni>* lowUniPtr;
	cin >> lowUni;
	Uni lowTemp = Uni(lowUni);
	int lowExist = UniTree.find(lowTemp, lowUniPtr);

	if(!highExist ||!lowExist )
	{
		if (!highExist)
		{
			cout << "����������ѧ�����֣���������ѧУ̫�ˣ����а���û���������֣���" << endl;
		}
		if (!lowExist)
		{
			cout << "������˶Է���ѧУ�����ǲ��Ǳ���ר����" << endl;
		}
		return;
	}

	int highPlace = UniGraph.getVertexPos(highUni); 
	int highComponent = UniSet.CollapsingFind(highPlace); 
	int lowPlace = UniGraph.getVertexPos(lowUni);
	int lowComponent = UniSet.CollapsingFind(lowPlace); 

	int success;
	if (highComponent == lowComponent)
	{
		success = 1; 
	}
	else
	{
		success = StrongConComGraph.existWay(highComponent, lowComponent); 
		if (!success)
		{
			cout << "�Բ������ѧУ������ζ����ܳ����Է���ѧУ~~~" << endl;;
			return;
		}
	}
	cout << "��ϲ������˶Է���ѧУ��" << endl;
	findchain(highPlace, lowPlace); 
}

void UCC::findchain(int& highPlace, int& lowPlace)
{
	int* visvertex = new int[UNINUM];
	int* visedge = new int[UNINUM];
	UniGraph.unweightedshortestpath(highPlace, lowPlace, visvertex, visedge);

	int x = lowPlace;

	Stack<int> vertexStack;
	Stack<int> edgeStack;

	int v = lowPlace;
	vertexStack.Push(v);

	int e = -1;//��ʼ��Ϊ�����ܵı�ֵ

	int nexte;
	while (1)
	{
		nexte = visedge[v];
		v = visvertex[v];

		if (e != nexte)
		{
			edgeStack.Push(nexte);
			vertexStack.Push(v);
			e = nexte;
		}
		if (v == highPlace)
		{
			break;
		}
	}

	while (!edgeStack.isEmpty())
	{
		int from = vertexStack.getTop();
		String fromUni = UniGraph.getValue(from);
		Uni tempfromUni = Uni(fromUni);
		vertexStack.Pop();

		int path = edgeStack.getTop();
		edgeStack.Pop();

		int to = vertexStack.getTop();
		String toUni = UniGraph.getValue(to);
		Uni temptoUni = Uni(toUni);

		AVLNode<Uni>* fromptr, * toptr;
		UniTree.find(tempfromUni, fromptr);
		UniTree.find(temptoUni, toptr);

		cout << setiosflags(ios::left);
		cout  << setw(RankingNameLength+1) << RankingName[path];
		cout << setw(UniNameLength) << fromUni << "#" << setw(RankingNameLength)<<fromptr->data.m_rank[path];
		cout << setw(UniNameLength) << toUni << "#" << setw(RankingNameLength) << toptr->data.m_rank[path];
		cout << endl;
	}

	vertexStack.Pop();
}
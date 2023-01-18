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
		cout << "请输入第" << i + 1 << "条大学排行榜名" << endl;
		String sranking;
		cin >> sranking;
		RankingName[i] = sranking;
		cout << "请按顺序输入大学排名(大小写不敏感),-1结束"<<endl;
		
		int tag = 0;//是否是排行榜第二个以后的大学
		int cnt = 0;
		String pre(UniNameLength), cur(UniNameLength);
		while (1)
		{
			cnt++;
			cout << "第" << cnt << "名大学:";
			cin >> cur; 
			cur.strlwr();//大学名字转换为小写，大小写不敏感
			if (cur == "-1")
			{
				break;
			}
			Uni u = Uni(cur); //使用大学名构造Uni变量
			u.setrank(i, cnt);  //设置大学在本条排行榜上的名次
			AVLNode<Uni>* ptr; 
			int  exist = UniTree.find(u,ptr);  //寻找该大学在搜索树上是否已存在
			 
			if (!exist)//不存在，插入搜索树和大学连通图
			{
				UniTree.insert(u); 
				UniGraph.insertVertex(cur); 
			}
			else//存在，与搜索树返回的指针指向内容合并排名记录内容
			{
				ptr->data.merge(u);  
			}
			if (tag)//与前一所大学在大学连通图上建单向边
			{
				int s = UniGraph.getVertexPos(pre);  
				int t = UniGraph.getVertexPos(cur);   
				UniGraph.insertEdge(s,t,i);   
			}
			tag = 1; 
			pre = cur;  
		}
	}

	tarjan(UniGraph, UniSet); //求强连通分量

	//根据原本的大学连通图，为所求的强连通分量建有向图
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
	cout << "请输入你的大学："<<endl;
	String highUni;
	AVLNode<Uni>* highUniPtr;
	cin >> highUni;
	Uni highTemp = Uni(highUni);
	int highExist =UniTree.find(highTemp, highUniPtr);
	 
	cout << "请输入对方的学校：" << endl;
	String lowUni;
	AVLNode<Uni>* lowUniPtr;
	cin >> lowUni;
	Uni lowTemp = Uni(lowUni);
	int lowExist = UniTree.find(lowTemp, lowUniPtr);

	if(!highExist ||!lowExist )
	{
		if (!highExist)
		{
			cout << "你输错了你大学的名字，或者这所学校太菜，排行榜上没有它的名字！！" << endl;
		}
		if (!lowExist)
		{
			cout << "你输错了对方的学校，它是不是本升专啦？" << endl;
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
			cout << "对不起，你的学校无论如何都不能超过对方的学校~~~" << endl;;
			return;
		}
	}
	cout << "恭喜你击败了对方的学校！" << endl;
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

	int e = -1;//初始化为不可能的边值

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
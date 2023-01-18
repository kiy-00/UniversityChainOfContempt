#include"Graph.h"

template<class T, class E>
Graphlnk<T, E>::Graphlnk(int sz)
{
	this->maxVertices = sz; this->numVertices = 0; this->numEdges = 0;
	NodeTable = new Vertex<T,E>[this->maxVertices];
	for (int i = 0; i < this->maxVertices; i++)
	{
		NodeTable[i].adj = NULL;
	}
}

template<class T, class E>
Graphlnk<T, E>::~Graphlnk()
{
	for (int i = 0; i < this->maxVertices; i++)
	{
		Edge<T, E>* p = NodeTable[i].adj;

		while (p != NULL)
		{
			NodeTable[i].adj = p->link;
			delete p;
			p = NodeTable[i].adj;
		}
	}
	delete[]NodeTable;
}


template<class T, class E>
T Graphlnk<T, E>::getValue(int i)
{
	return NodeTable[i].data;
}

template<class T, class E>
int Graphlnk<T, E>::getFirstNeighbor(int v)
{
	if (v < 0 || v >= this->numVertices)
	{
		return -1;
	}
	if (NodeTable[v].adj != NULL)
	{
		return NodeTable[v].adj->dest;
	}
	else
	{
		return -1;
	}
}

template<class T, class E>
int Graphlnk<T, E>::getNextNeighbor(int v, int w)
{
	if (v < 0 || v >= this->numVertices)
	{
		return -1;
	}
	Edge<T, E>* p = NodeTable[v].adj;
	while (p != NULL && p->dest != w)
	{
		p = p->link;
	}
	if (p != NULL && p->link != NULL)
	{
		return p->link->dest;
	}
	return -1;
}

template<class T, class E>
E Graphlnk<T, E>::getWeight(int v1, int v2)
{
	Edge < T, E>* p = NodeTable[v1].adj;
	while (p != NULL && p->dest != v2)
	{
		p = p->link;
	}
	if (p != NULL)
	{
		return p->cost;
	}
	return 0;
}

template<class T, class E>
bool Graphlnk<T, E>::insertVertex(T vertex)
{
	if (this->numVertices == this->maxVertices)
	{
		return false;
	}
	for (int i = 0; i < this->numVertices; i++)
	{
		if (vertex == NodeTable[i].data)
		{
			return false;
		}
	}
	NodeTable[this->numVertices].data=vertex;
	this->numVertices++;
	return true;
}

/*无向图的办法*/
template<class T, class E>
bool Graphlnk<T, E>::undirremoveVertex(int v)
{
	if (v < 0 || v >= this->numVertices)
	{
		return false;
	}
	Edge<T, E>* p, * s, * t;
	int i, k;
	while (NodeTable[v].adj != NULL)
	{
		p = NodeTable[v].adj; k = p->dest;
		s = NodeTable[k].adj;
		t = NULL;
		while (s != NULL && s->dest != v)
		{
			t = s; s = s->link;
		}
		if (s != NULL)
		{
			if (t == NULL)
			{
				NodeTable[k].adj = s->link;
			}
			else
			{
				t->link = s->link;
			}
			delete s;
		}
		NodeTable[v].adj = p->link;
		delete p;
		this->numEdges--;
	}
	this->numVertices--;
	NodeTable[v].data = NodeTable[this->numVertices].data;
	p = NodeTable[v].adj = NodeTable[this->numVertices].adj;
	while (p != NULL)
	{
		s = NodeTable[p->dest].adj;
		while (s != NULL)
		{
			if (s->dest == this->numVertices)
			{
				s->dest = v;
				break;
			}
			else
			{
				s = s->link;
			}
		}
		p = p->link;
	}
	return true;
}

/*有向图的办法*/
template<class T, class E>
bool Graphlnk<T, E>::dirremoveVertex(int v)
{
	if (v < 0 || v >= this->numVertices)
	{
		return false;
	}
	Edge<T, E>* p, * q;
	p = NodeTable[v].adj;
	while (p != NULL)
	{
		NodeTable[v].adj = p->link;
		delete p;
		p = NodeTable[v].adj;
	}
	for (int i = 0; i < this->numVertices; i++)
	{
		if (i == v)
		{
			continue;
		}
		p = NodeTable[i].adj;
		q = p;
		while (p != NULL)
		{
			if (p->dest == v)
			{
				q->link = p->link;
				delete p;
				p = q->link;
			}
			else
			{
				q = p;
				p = p->link;
			}
		}
	}
	this->numVertices--;
	NodeTable[v].data = NodeTable[this->numVertices].data;
	p = NodeTable[v].adj = NodeTable[this->numVertices].adj;
	while (p != NULL)
	{
		int s = NodeTable[p->dest].adj;
		while (s != NULL)
		{
			if (s->dest == this->numVertices)
			{
				s->dest = v;
				break;
			}
			else
			{
				s = s->link;
			}
		}
		p = p->link;
	}
	return true;
}

template<class T, class E>
bool Graphlnk<T, E>::insertEdge(int v1, int v2, E weight)
{
	if (v1 < 0 || v1 >= this->numVertices || v2 < 0 || v2 >= this->numVertices)
	{
		return false;
	}
	Edge<T, E>* p = NodeTable[v1].adj;
	while (p != NULL && p->dest != v2)
	{
		p = p->link;
	}
	if (p != NULL)
	{
		return false;
	}
	p = new Edge<T, E>;
	p->dest = v2; p->cost = weight; p->link = NodeTable[v1].adj; NodeTable[v1].adj = p;
	this->numEdges++;
	return true;
}

template<class T, class E>
bool Graphlnk<T, E>::removeEdge(int v1, int v2)
{
	if (v1 < 0 || v1 >= this->numVertices || v2 < 0 || v2 >= this->numVertices)
	{
		return false;
	}
	Edge<T, E>* p = NodeTable[v1].adj, *q = NULL;
	while (p != NULL && p->dest != v2)
	{
		q = p; p = p->link;
	}
	if (p == NULL)
	{
		return true;
	}
	else
	{
		if (q == NULL)
		{
			NodeTable[v1].adj = p->link;
		}
		else
		{
			q->link = p->link;
		}
		delete p;
	}
	return true;
}

template<class T, class E>
bool Graphlnk<T, E>::existWay(T start, T end)
{
	int startpoint = getVertexPos(start); 
	int endpoint = getVertexPos(end); 
	bool* visited = new bool[this->numVertices];
	for (int i = 0; i < this->numVertices; i++)
	{
		visited[i] = 0;
	}
	DFS(*this, startpoint, visited);
	int result=visited[endpoint];
	delete[]visited;
	return result;
}

template<class T, class E>
void DFS(Graph<T, E>& G, const T& v)
{
	int i, loc, n = G.NumberOfVertices();
	bool* visited = new bool[n];
	for (int i = 0; i < n; i++)
	{
		visited[i] = 0;
	}
	loc = G.getVertexPos(v);
	DFS(G, loc, visited);
	delete[]visited;
}

template<class T, class E>
void DFS(Graph<T, E>& G, int v, bool visited[])
{
	//G.getValue(v);
	visited[v] = 1;
	int w = G.getFirstNeighbor(v);
	while (w != -1)
	{
		if (visited[w] == 0)
		{
			DFS(G, w, visited);
		}
		w = G.getNextNeighbor(v, w);
	}
}

template<class T, class E>
void BFS(Graph<T, E>& G, const T& v)
{
	int i, w, n = G.NumberOfVertices();
	bool* visited = new bool[n];
	for (i = 0; i < n; i++)
	{
		visited[i] = 0;
	}
	int loc = G.getVertexPos(v);
	visited[loc] = 1;
	LinkedQueue<int> Q;
	Q.EnQueue(loc);
	while (!Q.isEmpty())
	{

		loc = Q.DeQueue();
		w = G.getFirstNeighbor(loc);
		while (w != -1)
		{
			if (visited[w] == 0)
			{
				G.getValue(w);
				visited[w] = 1;
				Q.EnQueue(w);
			}
			w = G.getNextNeighbor(loc, w);
		}
	}
	delete[]visited;
}

template<class T,class E>
void Graphlnk<T,E>::unweightedshortestpath(int start, int end, int visvertex[],E visedge[])
{
	int* dis = new int[this->numVertices];
	//int* vis = new int[numVertices];
	for (int i = 0; i < this->numVertices; i++)
	{
		visvertex[i] = -1;
		dis[i] = 0x7fffffff;
		//vis[i] = 0;
	}
	LinkedQueue<int> Q;
	Q.EnQueue(start);
	dis[start] = 0;
	//vis[start] = 1;
	while (!Q.isEmpty())
	{
		int from = Q.Front();
		if (from == end)
		{
			break;
		}
		Q.DeQueue();
		int nowdis = dis[from]+1;
		int to;
		Edge<T,E>* e=NodeTable[from].adj;
		for (to = getFirstNeighbor(from); to != -1; to = getNextNeighbor(from, to),e=e->link)
		{
			if (nowdis<dis[to])
			{
				dis[to] = nowdis;
				Q.EnQueue(to);
				visvertex[to] = from;
				visedge[to] = e->cost;
			}
		}
	}
}

template<class T, class E>
void ttarjan(Graphlnk<T, E>& G, UFsets& U, Stack<int>& S, int x, int dfn[], int low[], int instack[], int timer)
{
	timer++;
	dfn[x] = low[x] = timer;
	S.Push(x);
	instack[x] = 1;
	int y = G.getFirstNeighbor(x);
	while (y != -1)
	{
		if (dfn[y] == 0)
		{
			ttarjan( G, U, S, y, dfn, low, instack, timer);
			low[x] = min(low[x], low[y]);
		}
		else if (instack[y] == 1)
		{
			low[x] = min(low[x], low[y]);
		}
		y = G.getNextNeighbor(x, y);
	}
	if (dfn[x] == low[x])
	{
		while (1)
		{
			int temp = S.getTop();
			S.Pop();
			instack[temp] = 0; 
			if (temp == x)
			{
				break;
			}
			U.WeightedUnion(x, temp);
		}
		cout << endl;
	}
}

template<class T, class E>
void tarjan(Graphlnk<T, E>& G, UFsets& U)
{
	int n = G.NumberOfVertices();
	int* dfn = new int[n];
	int* low = new int[n];
	int* instack = new int[n];
	for (int i = 0; i < n; i++)
	{
		dfn[i] = low[i] = instack[i] = 0;
	}
	Stack<int> S;
	for (int i = 0; i < n; i++)
	{
		if (dfn[i] == 0)
		{
			ttarjan(G, U, S, i, dfn, low, instack, 0);
		}
	}

	delete[]dfn;
	delete[]low;
	delete[]instack;
}

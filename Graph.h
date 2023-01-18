#pragma once
#include"UFsets.h"
#include"Stack.cpp"
#include"LinkedQueue.cpp"
//const int maxWeight = 0x7fffffff;
const int DefaultVertices = 30;


template<class T, class E>
class Graph
{
public:
	Graph(int sz = DefaultVertices) {};
	virtual ~Graph() {};
	bool GraphEmpty()const
	{
		return numEdges == 0;
	}
	bool GraphFull()const
	{
		return numVertices == maxVertices || numEdges == (maxVertices) * (maxVertices - 1) / 2;
	}
	int NumberOfVertices()
	{
		return numVertices;
	}
	int NumberOfEdges()
	{
		return numEdges;
	}

	virtual int getFirstNeighbor(int v) = 0;
	virtual int getNextNeighbor(int v, int w) = 0;
	virtual bool insertVertex(const T vertex) = 0;
	virtual bool insertEdge(int v1, int v2, E cost) = 0;
	//virtual bool removeVertex(int v);
	virtual bool removeEdge(int v1, int v2) = 0;
	virtual int getVertexPos(T vertex) = 0;

protected:
	int maxVertices;
	int numEdges;
	int numVertices;
};



template<class T, class E>
class  Edge
{
public:
	int dest;
	E cost;
	Edge<T, E>* link;
	Edge() {};
	Edge(int num, E weight) :dest(num), cost(weight), link(NULL) {};
	bool operator!=(Edge<T, E>& R)const
	{
		return dest != R.dest;
	}
};

template<class T, class E>
class Vertex
{
public:
	T data;
	Edge<T, E>* adj;
};

template<class T, class E>
class Graphlnk :public Graph<T, E>
{
	//friend std::istream& operator >>(std::istream& cin, Graphlnk<T, E>& G);
	//friend std::ostream& operator <<(std::ostream& cout, Graphlnk<T, E>& G);

public:
	Graphlnk(int sz = DefaultVertices);
	~Graphlnk();
	int getFirstNeighbor(int v);
	int getNextNeighbor(int v, int w);
	T getValue(int i);
	E getWeight(int v1, int v2);
	bool insertVertex(T vertex);
	bool undirremoveVertex(int v);
	bool dirremoveVertex(int v);
	bool insertEdge(int v1, int v2, E weight);
	bool removeEdge(int v1, int v2);
	void unweightedshortestpath(int start, int end, int visver[], E visedge[]);
	int getVertexPos(const T vertex)
	{
		for (int i = 0; i < this->maxVertices; i++)
		{
			if (NodeTable[i].data == vertex)
			{
				return i;
			}
		}
		return -1;
	}
	bool existWay(T start, T end);
private:
	Vertex<T, E>* NodeTable;

};

/*
 * bfs.cpp
 *
 *  Created on: 23-Apr-2018
 *      Author: user
 */

#include <iostream>
#include <queue>
using namespace std;

struct Element
{
	Element(){key = 0;next = nullptr;};
	Element(int inKey){key = inKey;next = nullptr;};
	~Element(){};
	int key;
	Element* next;
};
typedef Element* ElementPtr;

struct Graph
{
	Graph(int numVertices)
	{
		this->numVertices = numVertices;
		adjList = new ElementPtr[numVertices];
		for(int i=0;i<numVertices;i++)
		{
			adjList[i] = nullptr;
		}
		state = new int[numVertices];
		d = new int[numVertices];
		parent = new int[numVertices];
	};
	~Graph(){};
	void insertInLinkedlist(int arrayIndex, int key)
	{
		ElementPtr element = new Element(key);
		element->next = adjList[arrayIndex];
		adjList[arrayIndex] = element;
	}
	void addEdge(int a,int b)
	{
//		a--;b--;
		insertInLinkedlist(a,b);
		insertInLinkedlist(b,a);
	}
	void dump()
	{
		for(int i=0;i<numVertices;i++)
		{
			cout << "Vertex " << i << " : " ;
			ElementPtr next = adjList[i];
			while(next != nullptr)
			{
				cout << next->key << " ";
				next = next->next;
			}
			cout << endl;
		}
	}
	ElementPtr* adjList;
	int* state;
	int* d;
	int* parent;
	int numVertices;
};

void BFS(Graph& g, int start)
{
	for(int i=0;i<g.numVertices;i++)
	{
		g.state[i] = 0;
		g.d[i] = 0;
		g.parent[i] = -1;
	}
	g.state[start] = 1;
	g.d[start] = 0;
	g.parent[start] = -1;
	queue<int> Q;
	cout << start << " ";
	Q.push(start);
	while(!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		ElementPtr next = g.adjList[u];
		while(next != nullptr)
		{
			int v = next->key;
			if(g.state[v]==0)
			{
				g.state[v] = 1;
				g.d[v] = g.d[v] +1;
				g.parent[v] = u;
				cout << v << " ";
				Q.push(v);
			}
			next = next->next;
		}
		g.state[u] = 2;
	}
	cout << endl;
}

int main()
{
	Graph graph(8);
	graph.addEdge(0,1);
	graph.addEdge(2,3);
	graph.addEdge(0,4);
	graph.addEdge(1,5);
	graph.addEdge(2,6);
	graph.addEdge(3,7);
	graph.addEdge(5,2);
	graph.addEdge(6,3);
	graph.addEdge(5,6);
	graph.addEdge(6,7);
	graph.dump();
	BFS(graph,0);
}

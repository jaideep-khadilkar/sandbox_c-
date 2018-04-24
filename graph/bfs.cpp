/*
 * bfs.cpp
 *
 *  Created on: 23-Apr-2018
 *      Author: user
 */

#include <iostream>
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
		arrayPtr = new ElementPtr[numVertices];
		for(int i=0;i<numVertices;i++)
		{
			arrayPtr[i] = nullptr;
		}
	};
	~Graph(){};
	void insertInLinkedlist(int arrayIndex, int key)
	{
		ElementPtr element = new Element(key);
		element->next = arrayPtr[arrayIndex];
		arrayPtr[arrayIndex] = element;
	}
	void addEdge(int a,int b)
	{
		a--;b--;
		insertInLinkedlist(a,b);
		insertInLinkedlist(b,a);
	}
	void dump()
	{
		for(int i=0;i<numVertices;i++)
		{
			cout << "Vertex " << i+1 << " : " ;
			ElementPtr next = arrayPtr[i];
			while(next != nullptr)
			{
				cout << next->key+1 << " ";
				next = next->next;
			}
			cout << endl;
		}
	}
	ElementPtr* arrayPtr;
	int numVertices;
};


int main()
{
	cout<< "Test" << endl;
	Graph graph(5);
	graph.addEdge(1,2);
	graph.addEdge(2,4);
	graph.addEdge(4,5);
	graph.addEdge(5,1);
	graph.addEdge(5,2);
	graph.addEdge(2,3);
	graph.addEdge(3,4);
	graph.dump();
}

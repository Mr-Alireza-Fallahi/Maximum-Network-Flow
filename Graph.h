#pragma once

#include "Node.h"
#include <deque>  // for deque
#include <map>  // for map
#include <utility>  // for pair and functions like make_pair

using std::deque;
using std::map;
using std::pair;

class Graph
{
	friend class Genetic;
private:
	unsigned short int volume;
	deque <Node*> graphNode;  // this is an array of nodes like v1,v2, etc
	deque <int> graphNodeName;  // this is just the name of nodes (used for genetic algorithm)
	Node* source,* sink;
	map <pair<Node*, Node*>, pair<int, int>> graph_Edge_Capacity_Flow;  // eg [(1,3),(10,0)]  means = v1 ---> v3 : capacity 10, flow 0
protected:
	void initialize();
	void generateNodes();
	void generateEdge();
	void addEdge(Node*, Node*, int, int);
	void addFlow(Node*, Node*, int);
	void setNodes();
public:
	Graph(int);
	~Graph();
	void show();
	deque <Node*> getNodes();
	map <pair<Node*, Node*>, pair<int, int>> getEdges();
};

#include "Graph.h"
#include <iterator>  // iterators are pointers to containers, make programing so easy
#include <cstdlib>  // for rand and srand 
#include <ctime>  // for time 
#include <iostream>

using std::make_pair;
using std::cout;
using std::endl;

void Graph::initialize()  // this function is for source and sink
{
	srand(time(0));
	source = new Node(0);
	sink = new Node(volume + 1);
	
	// adding source and sink to our graph with weight
	for (register int i = 0; i < volume; i++)
	{
		addEdge(this->source, graphNode.at(i), rand() % 10 + 5, 0);
		addEdge(graphNode.at(i), this->sink, rand() % 10 + 5, 0);
		addFlow(this->source, graphNode.at(i), rand() % (graph_Edge_Capacity_Flow[make_pair(this->source, graphNode.at(i))].first - 3) + 3);
		addFlow(graphNode.at(i), this->sink, (graph_Edge_Capacity_Flow[make_pair(this->source, graphNode.at(i))]).second);
	}

	graphNode.push_front(source);
	graphNode.push_back(sink);
}

void Graph::generateNodes()
{
	for (register int i = 1; i <= volume; i++)
	{
		graphNode.push_back(new Node(i));  // fill nodes from heap space
		graphNodeName.push_back(i); // fill name of nodes
	}
}

void Graph::generateEdge()  // in this function we generate capacity for each edge
{
	srand(time(0));
	for (register int i = 0; i < size(graphNode); i++)
	{
		for (register int j = 0; j < size(graphNode) - 1; j++)
		{
			addEdge(graphNode[i], graphNode[j + 1], rand() % 20 + 5, 0);  // the capacity size is between 5 and 25
			addFlow(graphNode[i], graphNode[j + 1], rand() % (graph_Edge_Capacity_Flow[make_pair(graphNode[i], graphNode[j + 1])].first));
		}
		addEdge(graphNode[i], graphNode[i], 0, 0);  // a node cannot have edge to itself 
		addFlow(graphNode[i], graphNode[i], 0);  // a node cannot have flow to itself 
	}
}

void Graph::addEdge(Node* source, Node* destination, int capacity, int flow = 0)
{
	// we consider the flow as zero here
	graph_Edge_Capacity_Flow[make_pair(source, destination)] = make_pair(capacity, flow);  // source ---> destination with weight of capacity (eg 7)
}

void Graph::addFlow(Node* source, Node* destination, int flow)
{
	graph_Edge_Capacity_Flow[make_pair(source, destination)].second = flow;
}

void Graph::setNodes()
{
	register map < pair<Node*, Node*>, pair<int, int> >::iterator itr;
	for (itr = begin(graph_Edge_Capacity_Flow); itr != end(graph_Edge_Capacity_Flow); itr++)
	{
		itr->first.first->addOutflow(itr->second.second);
		itr->first.second->addInflow(itr->second.second);
	}
}

Graph::Graph(int volumeNum) :
	volume(volumeNum)
{
	generateNodes();
	generateEdge();
	initialize();
	setNodes();
}

Graph::~Graph()
{
	for (register int i = 0; i < size(graphNode); i++)
	{
		delete graphNode.at(i);  // free the heap space we get from *new* syntax
		graphNode.at(i) = NULL;  // dangling pointer
	}
}

void Graph::show()
{
	cout << "Graph volume : " << this->volume << endl;
	for (register int i = 0; i < size(graphNodeName); i++)
	{
		cout << "v" << graphNodeName.at(i) << '\t';  // show the name and number of nodes
	}

	cout << "\n\nhere are the Vertices and their Weight with Flow : \n\n";
	register map < pair<Node*, Node*>, pair<int, int> >::iterator itr;  // iterators are easy way to get in loops
	for (itr = begin(graph_Edge_Capacity_Flow); itr != end(graph_Edge_Capacity_Flow); itr++)
	{
		cout << 'v' << itr->first.first->getName() << " ----> v" << itr->first.second->getName();  // show vertices edge
		cout << " || Capacity = " << itr->second.first << " and Flow = " << itr->second.second;  // show capacity and flow
		cout << " And the Balance Factor = " << itr->first.first->balanceFactor() << endl;
	}

	cout << std::endl << std::endl;
}

deque<Node*> Graph::getNodes()
{
	return deque<Node*>(this->graphNode);
}

map<pair<Node*, Node*>, pair<int, int>> Graph::getEdges()
{
	return map<pair<Node*, Node*>, pair<int, int>>(this->graph_Edge_Capacity_Flow);
}

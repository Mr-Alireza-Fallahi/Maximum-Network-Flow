#include "Node.h"
#include <cstdlib>

Node::Node() :
	name(0),
	inflow(0), 
	outflow(0)
{}

Node::Node(int item) :
	name(item),
	inflow(0),
	outflow(0)
{}

Node::~Node() {}

int Node::balanceFactor()
{
	return ((this->outflow) - (this->inflow));
}

void Node::addInflow(int item)
{
	this->inflow += item;
}

void Node::addOutflow(int item)
{
	this->outflow += item;
}

int Node::getName()
{
	return this->name;
}

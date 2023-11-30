#pragma once

class Node
{
	friend class Graph;
	friend class Genetic;
private:
	unsigned short int name;  // for example if the name was 1 we consider it as v1
	int inflow;  // number of inflows
	int outflow;  // number of outflows
public:
	Node();	
	Node(int);
	~Node();
	int balanceFactor();  // check whether the inflow and outflow are the same
	void addInflow(int);
	void addOutflow(int);
	int getName();
};

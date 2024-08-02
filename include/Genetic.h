#ifndef GENETIC_H
#define GENETIC_H

#include "Graph.h"
#include <vector>

using std::vector;

class Genetic
{
private:
	unsigned short int flow;
	int ParentMutation1, ParentMutation2, ChildMutation1, ChildMutation2, GeneMutation;
	Graph* graph;
	deque <Node*> Mutated_Gene;
	deque <Node*> population[10];  // our population
	deque <Node*> parents[2], childeren[2];  // our chosen Chromosomes for cross over
	map <pair<Node*, Node*>, pair<int, int>> Graph_Edges_For_Fittness;
	map <pair<Node*, Node*>, pair<int, int>> Edges_for_Mutation;
protected:
	void setGenetic();
	void Fittness_Function();
	void CrossOver();
	void Mutation(deque <Node*>);
	void ChoseChromosome();
	int getPrecedence(deque <Node*>);
	void showIteration();
	bool check_If_The_Best_Answer();  // this function is for terminating genetic algorithm 
	void run();
public:
	Genetic(Graph*);
	~Genetic();
};

#endif // !GENETIC_H

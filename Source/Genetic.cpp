#include "Genetic.h"
#include <algorithm>  // for shuffle
#include <queue>  // for priority queue
#include <cmath>  // for abs
#include <iostream>

using std::priority_queue;
using std::random_shuffle;
using std::min_element;
using std::make_pair;
using std::abs;
using std::cout;
using std::endl;

void Genetic::setGenetic()
{
	Graph_Edges_For_Fittness = graph->getEdges();  // this will get nodes for fittness 
	Edges_for_Mutation = graph->getEdges();  // this will get nodes for mutation

	for (register int i = 0; i < 10; i++)
	{
		// create random humans gor genetic algorithm
		population[i] = graph->getNodes();
		random_shuffle(begin(population[i]) + 1, end(population[i]) - 1);  // to differ the humans 
		// at the abouve code we don't shuffle the first(source) and last(sink) 
	}

	Mutated_Gene = population[rand() % 10];  // first initialization
	random_shuffle(begin(Mutated_Gene) + 1, end(Mutated_Gene) - 1);
}

void Genetic::Fittness_Function()
{;
	// we will add our population chromosomes in this queue in order to balance factor
	static priority_queue <pair <pair<int, int>, deque <Node*>>> Priority_Balance_and_Edge;
	if (Priority_Balance_and_Edge.size() == 0)
	{
		for (register int i = 0; i < size(population); i++)
		{
			int count(0);  // finding balance factor
			deque <Node*>::iterator itr;
			for (itr = begin(population[i]); itr != end(population[i]); itr++)
			{
				count += (*itr)->balanceFactor();  // finding the balance factor of nodes
			}

			int temp1, temp2;
			vector <int> residualCapacity;
			for (register int j = 0; j < size(population[i]) - 1; j++)
			{
				// this is for finding the residual network capacity edges
				temp1 = Graph_Edges_For_Fittness[make_pair(population[i].at(j), population[i].at(j + 1))].first;
				temp2 = Graph_Edges_For_Fittness[make_pair(population[i].at(j), population[i].at(j + 1))].second;
				residualCapacity.push_back(temp1 - temp2);
			}
			int minimum_Flow_Addition = *(min_element(begin(residualCapacity), end(residualCapacity)));  // understimated flow for chosen chromosome

			// adding the chromosomes to the queue in order to chose the best one
			Priority_Balance_and_Edge.push(make_pair(make_pair(minimum_Flow_Addition, -count), population[i]));
		}
	}
	
	// chosing parents by priority we set before
	parents[0] = Priority_Balance_and_Edge.top().second;
	Priority_Balance_and_Edge.pop();
	parents[1] = Priority_Balance_and_Edge.top().second;
	Priority_Balance_and_Edge.pop();
}

void Genetic::CrossOver()
{
	srand(time(0));
	int point = rand() % 2 + 3;  // between 3 and 5
	
	childeren[0].insert(begin(childeren[0]), begin(parents[0]), begin(parents[0]) + point);
	childeren[0].insert(begin(childeren[0]) + point, begin(parents[1]) + point, end(parents[1]));
	childeren[1].insert(begin(childeren[1]), begin(parents[1]), begin(parents[1]) + point);
	childeren[1].insert(begin(childeren[1]) + point, begin(parents[0]) + point, end(parents[0]));
}

void Genetic::Mutation(deque <Node*> gene)
{
	for (register int i = 0; i < size(gene) - 1; i++)
	{
		Edges_for_Mutation[make_pair(gene.at(i), gene.at(i + 1))].second += GeneMutation;
		gene.at(i)->addOutflow(GeneMutation), gene.at(i + 1)->addInflow(GeneMutation);
	}

	Graph_Edges_For_Fittness = Edges_for_Mutation;
	flow = gene.at(0)->outflow;
}

void Genetic::ChoseChromosome()  // for elitism
{
	priority_queue <pair<int, deque<Node*>>> Chosen;

	// choose between two parents, two children and one mutation in order to use mutation
	ParentMutation1 = getPrecedence(parents[0]);
	Chosen.push(make_pair(ParentMutation1, parents[0]));

	ParentMutation2 = getPrecedence(parents[1]);
	Chosen.push(make_pair(ParentMutation2, parents[1]));

	ChildMutation1 = getPrecedence(childeren[1]);
	Chosen.push(make_pair(ChildMutation1, childeren[0]));

	ChildMutation1 = getPrecedence(childeren[1]);
	Chosen.push(make_pair(ChildMutation2, childeren[0]));

	GeneMutation = getPrecedence(Mutated_Gene);
	Chosen.push(make_pair(GeneMutation, Mutated_Gene));

	Mutated_Gene = Chosen.top().second;
	GeneMutation = Chosen.top().first;
}

int Genetic::getPrecedence(deque<Node*> gene)
{
	vector <int> edges;
	int temp;
	for (register int i = 0; i < size(gene) - 1; i++)
	{
		// find the residual capacity for our genes 
		temp = Graph_Edges_For_Fittness[make_pair(gene[i], gene[i + 1])].first - Graph_Edges_For_Fittness[make_pair(gene[i], gene[i + 1])].second;
		edges.push_back(temp);
	}

	int precedence = *(min_element(begin(edges), end(edges)));
	return precedence;
}

void Genetic::showIteration()
{
	static unsigned int iteration = 1;

	cout << "Your " << iteration << " iteration is shown below : \n";
	deque <Node*>::iterator itr;
	for (itr = begin(Mutated_Gene); itr != end(Mutated_Gene); itr++)
	{
		cout << 'v' << (*itr)->getName() << '\t';
		if ((*itr)->getName() == (graph->volume + 1))
		{
			cout << endl;
		}
	}
	cout << endl << endl;
	iteration++;
}

bool Genetic::check_If_The_Best_Answer()
{
	return GeneMutation;
}

void Genetic::run()
{
	while (true)
	{
		try
		{
			Fittness_Function();
			CrossOver();
			ChoseChromosome();
			Mutation(Mutated_Gene);
			showIteration();
			if (!check_If_The_Best_Answer()) 
			{ 
				throw "\n\n--------------------------------------------\nAlgorithm is finished\n";
			}
		}
		catch (const char* expression)
		{
			cout << expression;
			cout << "Your maximum Network flow is ------> " << flow << endl;
			break;
		}
	}
}

Genetic::Genetic(Graph* given) :
	graph(given)
{
	setGenetic();
	run();
}

Genetic::~Genetic()
{
	cout << "Thanks for your Attention. Hope you enjoyed ...... \n\n\n";
}

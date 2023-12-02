#include <iostream>
#include "Graph.h"
#include "Genetic.h"

using std::cout;
using std::cin;

int main(void)
{
	system("color f0");
	cout << "------- In God We Trust ------- \n";
	cout << "--- Alireza Fallahi Represents :  \n\n\n\n";

	int GraphVolume;
	cout << "Enter your Graph volume : ";
	cin >> GraphVolume;

	Graph graph(GraphVolume);
	graph.show();

	Genetic Find_Max_Flow(&graph);

	return 0;
}
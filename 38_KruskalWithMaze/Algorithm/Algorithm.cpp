#include <iostream>

#include "Kruskal.h"

using namespace std;


int main()
{
	CreateGraph();

	vector<CostEdge> selected;
	int cost = Kruskal(selected);

	cout << cost << endl;
}
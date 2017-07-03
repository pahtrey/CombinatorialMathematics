// lab3.1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int V = 0;
int E = 0;
int graphWeight = 0;

struct Edge
{
	int v1, v2, weight;
};

struct Graph
{
	int V, E;
	Edge* edge;
};

struct subset
{
	int parent;
	int rank;
};

int findSetOfElement(struct subset subsets[], int i);
void UnionTwoSets(struct subset subsets[], int x, int y);

void Boruvka(struct Graph* graph, struct Graph* resultGraph)
{
	int V = graph->V, E = graph->E;
	Edge *edge = graph->edge;

	struct subset *subsets = new subset[V];

	int *cheapest = new int[V];

	for (int v = 0; v < V; ++v)
	{
		subsets[v].parent = v;
		subsets[v].rank = 0;
		cheapest[v] = -1;
	}

	int numTrees = V;

	while (numTrees > 1)
	{
		for (int i = 0; i < E; ++i)
		{
			int set1 = findSetOfElement(subsets, edge[i].v1);
			int set2 = findSetOfElement(subsets, edge[i].v2);

			if (!(set1 == set2))
			{
				if (cheapest[set1] == -1 || edge[cheapest[set1]].weight > edge[i].weight)
				{
					cheapest[set1] = i;
				}
				if (cheapest[set1] == -1 || edge[cheapest[set2]].weight > edge[i].weight)
				{
					cheapest[set2] = i;
				}
			}
			else
			{
				continue;
			}
		}

		for (int i = 0; i < V; ++i)
		{
			if (cheapest[i] != -1)
			{
				int set1 = findSetOfElement(subsets, edge[cheapest[i]].v1);
				int set2 = findSetOfElement(subsets, edge[cheapest[i]].v2);

				if (set1 == set2)
				{
					continue;
				}

				graphWeight += edge[cheapest[i]].weight;

				resultGraph->edge[i].v1 = edge[cheapest[i]].v1;
				resultGraph->edge[i].v2 = edge[cheapest[i]].v2;
				resultGraph->edge[i].weight = edge[cheapest[i]].weight;
				
				UnionTwoSets(subsets, set1, set2);
				numTrees--;
			}
			else
			{
				resultGraph->edge[i].v1 = -1;
				resultGraph->edge[i].v2 = -1;
				resultGraph->edge[i].weight = -1;
			}
		}
	}

	return;
}

struct Graph* createGraph(int V, int E)
{
	Graph* graph = new Graph;
	graph->V = V;
	graph->E = E;
	graph->edge = new Edge[E];
	return graph;
}

int findSetOfElement(struct subset subsets[], int i)
{
	if (subsets[i].parent != i)
	{
		subsets[i].parent = findSetOfElement(subsets, subsets[i].parent);
	}

	return subsets[i].parent;
}

void UnionTwoSets(struct subset subsets[], int x, int y)
{
	int xroot = findSetOfElement(subsets, x);
	int yroot = findSetOfElement(subsets, y);

	if (subsets[xroot].rank < subsets[yroot].rank)
	{
		subsets[xroot].parent = yroot;
	}
	else if (subsets[xroot].rank > subsets[yroot].rank)
	{
		subsets[yroot].parent = xroot;
	}
	else
	{
		subsets[yroot].parent = xroot;
		subsets[xroot].rank++;
	}
}

struct Graph* getParameters()
{
	ifstream inputFile("input.txt");
	string line;

	getline(inputFile, line);
	istringstream ss(line);
	ss >> V >> E;

	struct Graph* graph = createGraph(V, E);

	int v1, v2, weight, i = 0;
	while (inputFile >> v1 >> v2 >> weight && i <= V)
	{
		graph->edge[i].v1 = v1;
		graph->edge[i].v2 = v2;
		graph->edge[i].weight = weight;
		++i;
	}

	return graph;

}

void saveResults(struct Graph* resultGraph)
{
	ofstream outputFile;
	outputFile.open("output.txt");
	outputFile << graphWeight << endl;

	for (int i = 0; i < V; ++i)
	{
		if (resultGraph->edge[i].weight != -1)
		{
			outputFile << resultGraph->edge[i].v1 << " " << resultGraph->edge[i].v2 << " " << resultGraph->edge[i].weight << endl;
		}
	}

	outputFile.close();
}

int main()
{
	struct Graph* graph = getParameters();
	struct Graph* resultGraph = createGraph(V, E);

	Boruvka(graph, resultGraph);

	saveResults(resultGraph);

	return 0;
}
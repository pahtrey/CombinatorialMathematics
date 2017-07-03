// lab4.1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <algorithm>
using namespace std;

int countVertex = 0;

struct Edge
{
	int v;
	int flow;
	int C;
	int rev;
};

class Graph
{
	int V;
	int *level;
	vector<Edge> *adj;
public:
	Graph(int V)
	{
		adj = new vector<Edge>[V];
		this->V = V;
		level = new int[V];
	}

	void addEdge(int u, int v, int C)
	{
		Edge a{ v, 0, C, adj[v].size() };
		Edge b{ u, 0, 0, adj[u].size() };

		adj[u].push_back(a);
		adj[v].push_back(b);
	}

	bool BFS(int s, int t);
	int sendFlow(int s, int flow, int t, vector<int> start);
	int Dinic(int s, int t);
};

bool Graph::BFS(int s, int t)
{
	for (int i = 0; i < V; i++)
	{
		level[i] = -1;
	}

	level[s] = 0;

	list<int> q;
	q.push_back(s);

	vector<Edge>::iterator i;
	while (!q.empty())
	{
		int u = q.front();
		q.pop_front();
		for (i = adj[u].begin(); i != adj[u].end(); i++)
		{
			Edge &e = *i;
			if (level[e.v] < 0 && e.flow < e.C)
			{
				level[e.v] = level[u] + 1;
				q.push_back(e.v);
			}
		}
	}

	return level[t] < 0 ? false : true;
}

int Graph::sendFlow(int u, int flow, int t, vector<int> start)
{
	if (u == t)
	{
		return flow;
	}

	for (; start[u] < adj[u].size(); start[u]++)
	{
		Edge &e = adj[u][start[u]];

		if (level[e.v] == level[u] + 1 && e.flow < e.C)
		{
			int curr_flow = min(flow, e.C - e.flow);
			int temp_flow = sendFlow(e.v, curr_flow, t, start);

			if (temp_flow > 0)
			{
				e.flow += temp_flow;
				adj[e.v][e.rev].flow -= temp_flow;
				return temp_flow;
			}
		}
	}

	return 0;
}

int Graph::Dinic(int s, int t)
{
	if (s == t)
	{
		return -1;
	}

	int total = 0;

	while (BFS(s, t) == true)
	{
		vector<int> start(V + 1);

		while (int flow = sendFlow(s, INT_MAX, t, start)) {
			total += flow;
		}
	}

	return total;
}

Graph getParameters()
{
	ifstream inputFile("input.txt");
	string line;

	getline(inputFile, line);
	istringstream ss(line);
	ss >> countVertex;
	Graph g(countVertex);

	int v1, v2, sink;
	while (inputFile >> v1 >> v2 >> sink)
	{
		g.addEdge(v1, v2, sink);
	}

	return g;
}


void saveResult(int startVertex, int endVertex, int maxFlow)
{
	ofstream outputFile;
	outputFile.open("output.txt");
	outputFile << countVertex << endl;
	outputFile << startVertex << " " << endVertex << " " << maxFlow << endl;
	outputFile.close();
}

int main()
{
	Graph graph = getParameters();

	int startVertex = 0;
	int endVertex = countVertex - 1;

	int maxFlow = graph.Dinic(startVertex, endVertex);

	saveResult(startVertex, endVertex, maxFlow);

	return 0;
}
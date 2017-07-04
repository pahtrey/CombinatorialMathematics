// lab2.1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

vector<pair<int, int>> bridges;
vector<int> junctionPoints;
vector<vector<int>> graph;
vector<bool> used;
vector<int> timerIn;
vector<int> timerUp;
int timer;

void FindPoints(int vertex, int parent)
{
	used[vertex] = true;
	timerIn[vertex] = timerUp[vertex] = timer++;
	int children = 0;
	for (size_t i = 0; i < graph[vertex].size(); ++i)
	{
		int to = graph[vertex][i];
		if (to == parent)
		{
			continue;
		}
		if (used[to])
		{
			timerUp[vertex] = min(timerUp[vertex], timerIn[to]);
		}
		else
		{
			FindPoints(to, vertex);
			timerUp[vertex] = min(timerUp[vertex], timerUp[to]);
			if (timerUp[to] >= timerIn[vertex] && parent != -1)
			{
				junctionPoints.push_back(vertex);
			}
			++children;
		}
	}
	if (parent == -1 && children > 1)
	{
		junctionPoints.push_back(vertex);
	}
}

void FindBridges(int vertex, int parent)
{
	used[vertex] = true;
	timerIn[vertex] = timerUp[vertex] = timer++;
	for (size_t i = 0; i < graph[vertex].size(); ++i)
	{
		int to = graph[vertex][i];
		if (to == parent)
		{
			continue;
		}
		if (used[to])
		{
			timerUp[vertex] = min(timerUp[vertex], timerIn[to]);
		}
		else
		{
			FindBridges(to, vertex);
			timerUp[vertex] = min(timerUp[vertex], timerUp[to]);
			if (timerUp[to] > timerIn[vertex])
			{
				bridges.push_back(pair<int, int>(vertex, to));
			}
		}
	}
}

void SetGraph(vector<vector<int>> matrix)
{
	graph.swap(matrix);
	size_t matrixSize = graph.size();
	used = vector<bool>(matrixSize, false);
	timerIn.resize(matrixSize);
	timerUp.resize(matrixSize);
}

vector<vector<int>> GetParameters()
{
	ifstream inputFile("input.txt");
	string line;

	getline(inputFile, line);
	istringstream ss(line);

	int V, E;
	ss >> V;
	ss >> E;

	vector<vector<int>> matrix;

	matrix.resize(V);

	for (int i = 0; i < E; ++i)
	{
		int vertex1, vertex2;
		string tempString;
		getline(inputFile, tempString);
		ss.clear();
		ss.str(tempString);
		ss >> vertex1;
		ss >> vertex2;
		matrix[vertex1].push_back(vertex2);
		matrix[vertex2].push_back(vertex1);
	}

	return matrix;
}

void SaveResult()
{
	ofstream outputFile;
	outputFile.open("output.txt");
	string result = "no";

	for (size_t i = 0; i < junctionPoints.size(); ++i)
	{
		outputFile << junctionPoints[i] << " ";
	}
	outputFile << endl;

	for (size_t i = 0; i < bridges.size(); ++i)
	{
		outputFile << bridges[i].first << " " << bridges[i].second << endl;
	}
	outputFile.close();
}


int main()
{
	vector<vector<int>> matrix = GetParameters();

	SetGraph(matrix);
	FindPoints(0, -1);

	SetGraph(matrix);
	for (size_t i = 0; i < matrix.size(); ++i)
	{
		if (!used[i])
		{
			FindBridges(i, -1);
		}
	}
	SaveResult();
	return 0;
}
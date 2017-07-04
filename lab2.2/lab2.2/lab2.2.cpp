// lab2.2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

vector<vector<int>> graph;
vector<vector<int>> transposedGraph;
vector<char> used;
vector<int> order;
vector<int> q;

void DFS(int vertex)
{
	used[vertex] = true;
	for (size_t i = 0; i < graph[vertex].size(); ++i)
	{
		if (!used[i] && graph[vertex][i] != 0)
		{
			DFS(i);
		}
	}
	order.push_back(vertex);
}

void DFSTransposed(int vertex)
{
	used[vertex] = true;
	q.push_back(vertex);
	for (size_t i = 0; i < transposedGraph[vertex].size(); ++i)
	{
		if (!used[i] && transposedGraph[vertex][i] != 0)
		{
			DFSTransposed(i);
		}
	}
}

void Transpose()
{
	transposedGraph = vector<vector<int>>(graph.size(), vector<int>(graph.size()));
	for (size_t i = 0; i < graph.size(); ++i)
	{
		for (size_t j = 0; j < graph[i].size(); ++j)
		{
			transposedGraph[j][i] = graph[i][j];
		}
	}
}

bool IsStrongConnection()
{
	used.assign(graph.size(), false);
	for (size_t i = 0; i < graph.size(); ++i)
	{
		if (!used[i])
		{
			DFS(i);
		}
	}

	used.assign(graph.size(), false);
	DFSTransposed(order[graph.size() - 1]);

	return q.size() == graph.size();
}

vector<vector<int>> GetParameters()
{
	ifstream inputFile("input.txt");
	string line;

	getline(inputFile, line);
	istringstream ss(line);

	int countVertex;
	ss >> countVertex;

	vector<vector<int>> matrix;
	matrix.resize(countVertex);

	for (int i = 0; i < countVertex; ++i)
	{
		matrix[i].resize(countVertex);
		string tempString;
		getline(inputFile, tempString);
		ss.clear();
		ss.str(tempString);
		for (int j = 0; j < countVertex; ++j)
		{
			ss >> matrix[i][j];
		}
	}

	return matrix;
}

void SaveResult()
{
	ofstream outputFile;
	outputFile.open("output.txt");
	string result = "no";

	if (IsStrongConnection())
	{
		result = "yes";
	}

	outputFile << result << endl;
	outputFile.close();
}

int main()
{
	vector<vector<int>> matrix = GetParameters();
	graph.swap(matrix);
	Transpose();
	SaveResult();

	return 0;
}
// lab3.2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

const int MAX_VERTEX = 8;
int v = 0;
int graph[MAX_VERTEX][MAX_VERTEX];
int martix[MAX_VERTEX][MAX_VERTEX];

void KirchhoffMatrix()
{
	for (int i = 0; i < v; ++i)
	{
		int count = 0;
		for (int j = 0; j < v; ++j)
		{
			if (graph[i][j] == 1)
			{
				++count;
				martix[i][j] = -1;
			}
		}
		martix[i][i] = count;
	}
}

int Gauss(int a[MAX_VERTEX][MAX_VERTEX], int n)
{
	for (int i = 0; i < n; ++i)
	{
		bool found = false;
		for (int j = i; j < n; ++j)
		{
			if (a[j][i])
			{
				if (j != i)
				{
					swap(a[j], a[i]);
				}
				found = true;
				break;
			}
		}

		if (!found)
		{
			return 0;
		}

		for (int k = i + 1; k < n; ++k)
		{
			while (true)
			{
				int del = a[k][i] / a[i][i];
				for (int j = i; j < n; ++j)
				{
					a[k][j] -= del * a[i][j];
				}
				if (a[k][i] == 0)
				{
					break;
				}
				else
				{
					swap(a[k], a[i]);
				}
			}
		}
	}
	long res = 1;
	for (int i = 0; i < n; ++i)
	{
		res *= a[i][i];
	}
	return abs(res);
}

void getParameters()
{
	ifstream inputFile("input.txt");
	string line;

	getline(inputFile, line);
	istringstream ss(line);
	ss >> v;

	for (int i = 0; i < v; ++i)
	{
		getline(inputFile, line);
		istringstream ss(line);
		for (size_t j = 0; j < v; ++j)
		{
			ss >> graph[i][j];
			if (graph[i][j] > 0) graph[i][j] = 1;
		}
	}
}

void saveResults(int determinant)
{
	ofstream outputFile;
	outputFile.open("output.txt");
	outputFile << determinant << endl;
	outputFile.close();
}

int main()
{
	getParameters();
	KirchhoffMatrix();

	int dm[MAX_VERTEX][MAX_VERTEX];
	for (int i = 1; i < v; ++i)
	{
		for (int j = 1; j < v; ++j)
		{
			dm[i - 1][j - 1] = martix[i][j];
		}
	}
	int determinant = Gauss(dm, v - 1);

	saveResults(determinant);

	return 0;
}
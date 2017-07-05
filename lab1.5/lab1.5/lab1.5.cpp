// lab1.5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
using namespace std;

int maxValue = 0;
int maxWeight = 0;
int maxb[255] = {};

int Permutations(int n, int t, int w[], int c[])
{
	int i = 0;
	int k = 0;
	int b[255] = {};
	int maxItems = 0;

	k = t / *min_element(w, w + n);

	for (int i = 0; i < k; ++i)
	{
		b[i] = 0;
	}

	while (b[k] != 1)
	{
		i = 0;
		while (b[i] == n - 1)
		{
			b[i] = 0;
			i = i + 1;
		}
		b[i] = b[i] + 1;

		int value = 0;
		int weight = 0;
		for (int i = 0; i < k; ++i)
		{
			if (weight + w[b[i]] > t)
			{
				if (maxValue < value)
				{
					maxWeight = weight;
					maxValue = value;
					maxItems = i;
					for (int j = 0; j < i; ++j)
					{
						maxb[j] = b[j];
					}
				}
				break;
			}
			weight += w[b[i]];
			value += c[b[i]];
		}

		if (weight <= t && value > maxValue)
		{
			maxWeight = weight;
			maxValue = value;
			maxItems = k;
			for (int j = 0; j < k; ++j)
			{
				maxb[j] = b[j];
			}
		}
	}

	return maxItems;
}

int main()
{
	int n = 0;
	int t = 0;
	int w[255] = {};
	int c[255] = {};

	ifstream inputFile("input.txt");
	string line;

	getline(inputFile, line);
	istringstream ss(line);
	ss >> n >> t;

	for (size_t i = 0; i < n; ++i)
	{
		getline(inputFile, line);
		istringstream ss(line);
		ss >> w[i] >> c[i];
	}

	int result = Permutations(n, t, w, c);

	ofstream outputFile;
	outputFile.open("output.txt");

	outputFile << "Maximum value: " << maxValue << endl;
	outputFile << "Maximum weight: " << maxWeight << endl;

	outputFile << "Items: ";
	for (int i = 0; i < n; ++i)
	{
		int itemsCount = 0;
		for (int j = 0; j < result; ++j)
		{
			if (maxb[j] == i) itemsCount++;
		}
		outputFile << itemsCount << " ";
	}
	outputFile << endl;
	outputFile.close();

	return 0;
}
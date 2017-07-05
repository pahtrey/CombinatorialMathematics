// lab1.2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <time.h>
using namespace std;

void Combinations(int n)
{
	cout << "N: " << n << endl;

	int c[10] = {};
	int k = 5;

	for (int i = 1; i <= k; ++i)
	{
		c[i] = i;
	}

	int j = 1;

	clock_t time;
	time = clock();

	while (j != 0)
	{
		j = k;
		while (c[j] == n - k + j && c[j] > 0)
		{
			j = j - 1;
		}
		c[j] = c[j] + 1;

		for (int i = j + 1; i <= k; ++i)
		{
			c[i] = c[i - 1] + 1;
		}
	}

	time = clock() - time;
	cout << "Time: " << (double)time / CLOCKS_PER_SEC << endl;
}

int main()
{
	Combinations(10);
	Combinations(20);
	Combinations(25);
	Combinations(50);
	Combinations(100);

	system("pause");
	return 0;
}
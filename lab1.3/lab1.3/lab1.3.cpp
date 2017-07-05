// lab1.3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <time.h>
using namespace std;

void Permutations(int n)
{
	int p[20] = {},
		s[20] = {},
		d[20] = {};

	int m = 0, count = 0;

	for (int i = 1; i <= n; ++i)
	{
		p[i] = s[i] = i;
		d[i] = -1;
	}
	d[1] = 0;
	s[0] = s[n + 1] = m = n + 1;

	clock_t time;
	time = clock();

	while (m != 1)
	{
		m = n;
		while (s[p[m] + d[m]] > m)
		{
			d[m] = -d[m];
			m = m - 1;
		}
		int buffer = 0;
		buffer = s[p[m]];
		s[p[m]] = s[p[m] + d[m]];
		s[p[m] + d[m]] = buffer;

		buffer = p[s[p[m]]];
		p[s[p[m]]] = p[m];
		p[m] = buffer;

		++count;
	}
}

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
		Permutations(k);
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
	Combinations(5);
	Combinations(10);
	Combinations(20);
	Combinations(25);
	Combinations(50);
	Combinations(100);
	
	system("pause");
    return 0;
}


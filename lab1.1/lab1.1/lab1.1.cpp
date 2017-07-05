// lab1.1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <time.h>
using namespace std;

void Permutations(int n, bool showInConsole)
{
	cout << "N: " << n << endl;
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
		if (showInConsole)
		{
			for (int i = 1; i <= n; i++)
			{
				cout << p[i];
			}
			cout << endl;
		}
		
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

	time = clock() - time;
	cout << "Time: " << (double)time / CLOCKS_PER_SEC << endl;
	cout << "Count combinations: " << count << endl;
}

int main()
{
	// 1 параметр кол-во, 2 параметр выводить перестановки в консоль
	Permutations(4, true);
	Permutations(10, false);
	Permutations(11, false);
	Permutations(12, false);

	system("pause");
	return 0;
}
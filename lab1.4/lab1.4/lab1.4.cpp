// lab1.4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;

void RandomPermutations(int p[], int n)
{
	for (int i = 0; i < n; ++i)
	{
		p[i] = -1;
	}
	srand((int)time(0));
	for (int i = 0; i < n; ++i)
	{
		int random;
		do {
			random = rand() % n;
		} while (p[random] != -1);
		p[random] = i;
	}
}

int main()
{
	int n = 7; // длина
	int p[100] = {};

	RandomPermutations(p, n);

	for (int i = 0; i < n; ++i)
	{
		cout << p[i] << " ";
	}
	cout << endl;

	system("pause");
	return 0;
}
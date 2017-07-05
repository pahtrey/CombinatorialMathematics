// lab1.6.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <string>
#include <array>
using namespace std;

int Decode(string &str)
{
	array<unsigned long, 101> number;
	number.fill(0);
	number[str.length()] = 1;
	number[str.length() - 1] = str[str.length() - 1] != '0';
	for (size_t i = str.length() - 2; i < 101; --i)
	{
		if (str[i] == '0')
		{
			number[i] = 0;
		}
		else if (str[i] == '1' || (str[i] == '2' && str[i + 1] <= '6'))
		{
			number[i] = number[i + 1] + number[i + 2];
		}
		else
		{
			number[i] = number[i + 1];
		}
	}
	return number[0];
}

int main()
{
	ifstream inputFile("input.txt");
	string line;

	getline(inputFile, line);

	cout << "Count: " << Decode(line) << endl;
	system("pause");

	return 0;
}
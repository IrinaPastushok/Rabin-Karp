#include "Rabin-Karp.h"
#include <fstream>
#include  <iostream>
#include <string>
#include <math.h>
#include <clocale>
#include <Windows.h>
using namespace std;
void output(const string str, int shift, int tmp, int len_of_range)
{
	if (tmp == 0)
	{
		cout << "String Is Not Found!";
	}
	else
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		for (int i = 0; i < str.length(); i++)
		{
			if ((i >= shift) && (i < len_of_range + shift))
			{
				SetConsoleTextAttribute(hConsole, 13);
				cout << str[i];
			}
			else
			{
				SetConsoleTextAttribute(hConsole, 15);
				cout << str[i];
			}
		}
		cout << "\n";
		SetConsoleTextAttribute(hConsole, 15);
		cout << "Shift: " << shift << endl;
	}
}
long double hash_gorner(const string str, int len_of_range, int start, long double res_of_last_range)
{
	const long double mod = 1000000000000.00;//9223372036854775807.00
	const int coefficient = 10;
	if (start == 0)
	{
		res_of_last_range = str[0];
		for (int i = start + 1; i < len_of_range; i++)
		{
			res_of_last_range = str[i] + coefficient * res_of_last_range;
		}
	}
	else
	{
		res_of_last_range = coefficient * (res_of_last_range - (pow(coefficient, len_of_range - 1) *
			str[start - 1])) + str[len_of_range + start - 1];//russian text
	}
	if ((res_of_last_range >= mod) || (res_of_last_range < 0))
	{
		if (res_of_last_range >= mod)
		{
			while (res_of_last_range >= mod)
				res_of_last_range = res_of_last_range - mod;
		}
		if (res_of_last_range < 0)
		{
			while (res_of_last_range < 0)
				res_of_last_range = res_of_last_range + mod;
		}
	}
	return res_of_last_range;

}
void algoritm(const string cmp)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	string str_from_file;
	int tmp = 0;
	int len_cmp = cmp.length();
	int start = 0;
	long double hash_of_cmp = hash_gorner(cmp, len_cmp, 0, 0.0); //O(m)
	ifstream file("Text.txt");
	if (!file)
	{
		cout << "Can Not Found Of File!";
		goto key;
	}
	while (!file.eof())
	{
		start = 0;
		long double res_of_hash = 0;
		getline(file, str_from_file);
		if (str_from_file.length() >= cmp.length())
		{
			res_of_hash = hash_gorner(str_from_file, len_cmp, start, res_of_hash);//O(m)
			while (start <= str_from_file.length() - cmp.length())//O(n - m + 1)
			{
				if (res_of_hash == hash_of_cmp)
				{
					int count_of_coincidences = 0;
					for (int j = 0, k = start; j < len_cmp; j++, k++)//O(m)
					{
						if (cmp[j] == str_from_file[k])
						{
							count_of_coincidences++;
						}
					}
					if (count_of_coincidences == len_cmp)
					{
						if (tmp == 0)
						{
							cout << "Strings:" << "\n";
						}
						tmp++;
						output(str_from_file, start, tmp, cmp.length());
						break;
					}
				}
				start++;
				res_of_hash = hash_gorner(str_from_file, len_cmp, start, res_of_hash);//O(1)
			}
		}
	}
	file.close();
	if (tmp == 0)
	{
		output(cmp, 0, tmp, 0);
	}
key:;
}

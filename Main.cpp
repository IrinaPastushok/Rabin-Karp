#define _CRT_SECURE_NO_WARNINGS
#include "Rabin-Karp.h"
#include <iostream>
#include <string>
#include <clocale>
#include <Windows.h>
using namespace std;
int main()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	cout << "Enter The Sub-String:\n";
	string s;
	getline(cin, s);
	if (s == "")
	{
		cout << "Sorry, You Not Enter The String!";
		return -10;
	}
	algoritm(s);
	return 0;
}

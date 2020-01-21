#include <conio.h>
#include <iostream>
#include "menu.h"

using namespace std;

int print_menu(int i)
{
	const int n = 3;
	string str[n] = { "Game", "Demo", "Exit" };
	string point = ">> ";
	string empty = "   ";
	string change[n];
	for (int j = 0; j < n; j++)
		change[j] = empty;

	change[i] = point;

	system("cls");
	cout << "\tSEA BATTLE\n\n";
	for (int j = 0; j < n; j++)
		cout << "\t" << change[j] << str[j] << endl;
	return n;
}

int print_exit(int i)
{
	const int n = 2;
	string str[n] = { "YES", "NO" };
	string point = ">> ";
	string empty = "   ";
	string change[n];
	for (int j = 0; j < n; j++)
		change[j] = empty;

	change[i] = point;

	system("cls");
	cout << "\tEXIT?\n\n";
	for (int j = 0; j < n; j++)
		cout << "\t" << change[j] << str[j] << endl;
	return n;
}

int print_menu2(int i)
{
	const int n = 4;
	string str[n] = { " 5x5", "10x10", "15x15", " Back" };
	string point = ">> ";
	string empty = "   ";
	string change[n];
	for (int j = 0; j < n; j++)
		change[j] = empty;

	change[i] = point;

	system("cls");
	cout << "\tChoose size:\n\n";
	for (int j = 0; j < n; j++)
		cout << "\t" << change[j] << str[j] << endl;
	return n;
}

void menu(int n_menu)
{

	Menu m[3];
	Menu* p;
	p = m;
	m[0].name = 0;
	m[1].name = 1;
	m[2].name = 2;
	int i = n_menu;
	bool enter = false;
	for (;;)
	{
		p = change_menu(p, i);
		i = m[i].next;
		if (i == 2)
		{
			sea_battle((m[1].choose + 1) * 5, (m[1].choose + 1) * 2, m[0].choose);
			i = 0;
			getchar();
			getchar();
		}
		if (i == -1)
			exit(0);
	}
}

Menu *change_menu(Menu *m, int index)
{
	int i = 0, x;
	int n = 0;
	bool enter = false;
	do {
		if (m[index].name == 0)
			n = print_menu(i);
		if (m[index].name == 1)
			n = print_menu2(i);
		if (m[index].name == 2)
			n = print_exit(i);
		x = _getch();
		switch (x)
		{
		case 80:
			if (i + 1 < n)
				i++;
			break;
			/*case 77:
				if (j + 1 < n)
					j++;
				break;*/
		case 72:
			if (i - 1 >= 0)
				i--;
			break;
			/*case 75:
				if (j - 1 >= 0)
					j--;
				break;*/
		case 13:
			enter = true;
		}
	} while (!enter);

	if(i == n - 1)
		m[index].next = index - 1;
	else
	{
		m[index].next = index + 1;
		m[index].choose = i;
	}

	return m;
}
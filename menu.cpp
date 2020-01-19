#include <conio.h>
#include "header.h"

Menu* change_menu(Menu* m, int index);
void menu(int n_menu);

void close()
{
	exit(0);
}

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

	Menu m[2];
	Menu* p;
	p = m;
	m[0].name = 0;
	m[1].name = 1;
	//m[0].next = 0;
	int i = 0;
	bool enter = false;
	for (;;)
	{
		p = change_menu(p, i);
		i = m[i].next;
		if (i == 2)
		{
			sea_battle((m[1].choose + 1) * 5, (m[1].choose + 1) * 2, m[0].choose);
			i = 0;
			_getch();
			_getch();
		}
		if (i == -1)
			exit(0);
	}
}

Menu *change_menu(Menu *m, int index)
{
	int i = 0, x, n;
	bool enter = false;
	do {
		if (m[index].name == 0)
			n = print_menu(i);
		if (m[index].name == 1)
			n = print_menu2(i);
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
	m[index].next = index + 1;
	m[index].choose = i;
	if (index == 1)
		m[index].next = 2;
	if(/*index == 1 && i == 3*/ i == n - 1)
		m[index].next = index - 1;
	
	return m;
}
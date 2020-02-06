#include <conio.h>
#include "sea_battle.h"

using namespace std;

void print_menu(char str[][20], const int n, int i)
{
	char point[] = ">> ";
	char empty[] = "   ";
	char *change[4];
	for (int j = 0; j < n; j++)
		change[j] = empty;
	change[i] = point;

	system("cls");
	cout << "\t"<< str[0] << "\n\n";
	for (int j = 0; j < n; j++)
		cout << "\t" << change[j] << str[j + 1] << endl;
}

Menu* change_menu(Menu* m, char str[][20], int index)
{
	int i = 0, x, n;
	bool enter = false;

	do
	{
		print_menu(str, m[index].count, i);
		n = m[index].count;
		x = _getch();
		switch (x)
		{
		case Down:
			if (i + 1 < n)
				i++;
			break;

		case Up:
			if (i - 1 >= 0)
				i--;
			break;
		case Enter:
			enter = true;
		}
	} while (!enter);

	m[index].choose = i;

	return m;
}

int menu(int n_menu)
{
	Menu m[3];

	char str[3][5][20]
	{
		{ "SEA BATTLE" ,"Game", "Demo", "Exit" },
		{ "Choose Size", " 5x5", "10x10", "15x15", " Back" },
		{ "Back to Menu", "Yes", "No" },
	};

	int count[3] = { 3, 4, 2};

	for (int i = 0; i < 3; i++)
	{
		m[i].name = i;
		m[i].count = count[i];
		m[i].next = m[i].name + 1;
		m[i].previous = m[i].name - 1;
	}
	m[1].next = 10;
	m[2].previous = 7;

	int i = n_menu;
	bool enter = false;
	for (;;)
	{
		change_menu(m, str[i], i);
		if (m[i].choose == m[i].count - 1)
			i = m[i].previous;
		else
			i = m[i].next;
		if (i == 10)
		{
			sea_battle((m[1].choose + 1) * 5, m[0].choose);
			i = 0;
		}
		if (i == -1)
			exit(0);
		if (i == 7)
			return 0;
		if (i == 3)
			return 1;
	}
	return 0;
}
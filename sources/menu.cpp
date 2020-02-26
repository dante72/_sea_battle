#include <conio.h>
#include "sea_battle.h"

const int g = 7;
Menu g_m[g];
char g_str[g][5][20]
{
	{ "SEA BATTLE" ,"Game", "Demo", "Options", "Exit" },
	{ "Choose size", " 5x5", "10x10", "15x15", " Back" },
	{ "Back to Menu", "Yes", "No" },
	{ "Options", "Game mode", "Generator", "Themes", "Back" },
	{ "Game mode", "Standart", "Alternative" },
	{ "Themes", "Theme1", "Theme2", "Back" },
	{ "Generator", "Turn OFF", "Turn ON" }
};
int g_count[g]{ 4, 4, 2, 4, 2, 3, 2 };
int g_path[g][4]{
					{1, 1, 3, -1},
					{10, 10, 10, 0},
					{11, 12},
					{4, 6, 5, 0},
					{3, 3},
					{13, 13, 3},
					{3, 3}
};

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
	Modes mode;
	int i = n_menu;

	if (i == -1)
	{
		for (int j = 0; j < g; j++)
		{
			g_m[j].name = j;
			g_m[j].count = g_count[j];
			g_m[j].choose = 0;
		}
		i = 0;
	}
	for (;;)
	{
		change_menu(g_m, g_str[i], i);
		i = g_path[i][g_m[i].choose];
		switch (i)
		{
		case 10:
				mode.mode = g_m[4].choose;
				mode.m_generator = g_m[6].choose;
				mode.demo = g_m[0].choose;
				sea_battle((g_m[1].choose + 1) * 5, mode);
				i = 0;
				break;
		case -1:
				exit(0);
		case 12:
				return 0;
		case 11:
				return 1;
		case 13:
			change_theme(g_m[5].choose);
			i = 5;
			break;
		}
	}

	return 0;
}
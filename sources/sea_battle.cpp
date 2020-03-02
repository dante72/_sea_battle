#include <conio.h>
#include "sea_battle.h"

Unit **g_m[2];

using namespace std;

bool ship_is_destroyed(Unit** m, const int nn, int i, int j)
{
	int vector = 0;
	int head = ship_head(m, nn, i, j);
	int a = head / nn;
	int b = head % nn;
	int size = m[i][j].value;

	//if (a + 1 < nn && m[a + 1][b].value > 0)
		//	vector = 0;
	if (b + 1 < nn && m[a][b + 1].value > 0)
			vector = !vector;

	for (int k = a; k <= a + (size - 1) * !vector; k++)
		for (int p = b; p <= b + (size - 1) * vector; p++)
			if (m[k][p].status == 0)
				return false;

	return true;
}

Unit** area_of_the_destroyed_ship(Unit** m, const int nn, int i, int j)
{
	int vector = 0;
	int head = ship_head(m, nn, i, j);
	int a = head / nn;
	int b = head % nn;
	int size = m[a][b].value;

	//if (a + 1 < nn && m[a + 1][b].value > 0)
		//	vector = 0;
	if (b + 1 < nn && m[a][b + 1].value > 0)
		vector = !vector;
	for (int k = a - 1; k <= a + 1 + (size - 1) * !vector; k++)
		for (int p = b - 1; p <= b + 1 + (size - 1) * vector; p++)
		{
			if (!(k >= 0 && k < nn) || !(p >= 0 && p < nn))
				continue;
			if (m[k][p].status == 0)
				m[k][p].status = 1;
		}

	return m;
}

Player *battle_shoot(Player *pl, const int nn, bool demo, int index)
{
	Player p;

	p = pl[index];
	if (!demo && index == 1)
	{
		p.r = scan_point(pl, nn, index);
	}
	else
	{
		if (!p.under_attack)
			p.r = random_shoot(p.m, nn);
		else
			p.r = aim_shoot(p.m, nn, p.last_hit / nn, p.last_hit % nn);
	}
	p.m[p.r / nn][p.r % nn].status = true;
	if (p.m[p.r / nn][p.r % nn].value > 0)
	{
		p.last_hit = p.r;

		if (!ship_is_destroyed(p.m, nn, p.r / nn, p.r % nn))
		{
			p.status = 1;
			p.under_attack = true;
		}
		else
		{
			p.m = area_of_the_destroyed_ship(p.m, nn, p.r / nn, p.r % nn);
			p.status = 2;
			p.under_attack = false;
		}
	}
	else
	{
		p.status = 0;
	}
	pl[index] = p;

	return pl;
}

int count_ships(Unit** m, const int nn, bool flag)
{
	int k = 0;

	for (int i = 0; i < nn; i++)
		for (int j = 0; j < nn; j++)
			if (m[i][j].value > 0 && m[i][j].status && flag || m[i][j].value > 0 && !m[i][j].status && !flag)
				k++;

	return k;
}

int sea_battle(const int nn, Modes mode)
{
	Player p[2];
	bool demo = mode.demo;
	
	for (int i = 0; i < 2; i++)
	{
		p[i].m = create_map(nn);
		g_m[i] = p[i].m;
	}
	for (int i = 0; i < 2; i++)
	{
		p[i].m = map_gen(p[i].m, nn, mode);
		p[i].under_attack = false;
		p[i].r = 0;
		p[i].status = -1;
	}

	int index = rand() % 2;
	system("cls");
	print(p, nn, demo, -1, -1);
	cout << "\n\t";
	print_player(index, demo);
	cout << "is  first!" << endl << "\n\n\tPress ENTER...";
	getchar();
	system("cls");
	int k = count_ships(p[0].m, nn, 0);
	while (k != count_ships(p[0].m, nn, 1) && k != count_ships(p[1].m, nn, 1))
	{	
		if (demo && press_button() == ESC)
		{
			if (exit_menu() == 1)
			{
				free_m();
				menu(0);
			}
			else
			{
				print_all(p, nn, index, demo, p[1].r, p[0].r);
				continue;
			}
		}
		battle_shoot(p, nn, demo, index);
		print_all(p, nn, index, demo, p[1].r, p[0].r);
		if (p[index].status == 0)
			index = (++index) % 2;
	}
	for (int i = 0; i < 2; i++)
	{
		ft_delete(p[i].m);
	}
	cout << "\n\t";
	print_player(index, demo);
	cout << "win!" << endl << "\t\tGame Over" << endl << "\n\tPress ENTER...";
	getchar();

	return 0;
}

int exit_menu()
{
	if (menu(2) == 1)
		return 1;

	return 0;
}

void free_m()
{
	for (int i = 0; i < 2; i++)
		ft_delete(g_m[i]);
}

int press_button()
{
	int button;

	do
	{
		button = _getch();
	} while (!(button == ESC || button == Enter || button == Space));

	return button;
}
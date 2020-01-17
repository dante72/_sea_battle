#include "header.h"

int count_ships(Unit** m, const int nn, bool flag)
{
	int k = 0;
	for (int i = 0; i < nn; i++)
		for (int j = 0; j < nn; j++)
			if (m[i][j].value > 0 && m[i][j].status && flag || m[i][j].value > 0 && !m[i][j].status && !flag)
				k++;
	return k;
}

void sea_battle(const int nn, int max_size, bool demo)
{
	Player p[2];
	for (int i = 0; i < 2; i++)
	{
		Unit** m = create_squard(nn);
		m = matrix_value(m, nn, 0, 0);
		m = map_generator(m, nn, max_size);
		p[i].m = m;
		p[i].under_attack = false;
		p[i].r = 0;
		p[i].status = -1;
	}

	int index = rand() % 2;
	system("cls");
	print(p, nn, demo, -1, -1);
	cout << "\n\t";
	print_player(index, demo);
	cout << "is  first!";
	getchar();

	int k = count_ships(p[0].m, nn, 0);
	while (k != count_ships(p[0].m, nn, 1) && k != count_ships(p[1].m, nn, 1))
	{
		if (index == 1 && !demo)
		{
			p[index].r = scan_point(p, nn, index);
		}

		p[index] = battle_shoot(p[index], nn, demo, index);
		print_all(p, nn, index, demo, p[1].r, p[0].r);
		if (p[index].status == 0)
			index = (++index) % 2;
		//if (demo)
			//getchar();
	}

	for (int i = 0; i < 2; i++)
	{
		delete[] p[i].m;
	}
	cout << "\n\t";
	print_player(index, demo);
	cout << "win!" << endl << "\t\tGame Over";
}
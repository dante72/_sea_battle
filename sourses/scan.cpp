#include <conio.h>
#include "sea_battle.h"

int scan_point(Player* p, const int nn, int index)
{
	int i = p[1].r / nn;
	int j = p[1].r % nn;
	int x;
	bool enter = false;

	do {
		print_all(p, nn, index, false, nn * i + j, p[0].r);
		x = _getch();
		switch (x)
		{
		case Down:
			if (i + 1 < nn)
				i++;
			break;
		case Right:
			if (j + 1 < nn)
				j++;
			break;
		case Up:
			if (i - 1 >= 0)
				i--;
			break;
		case Left:
			if (j - 1 >= 0)
				j--;
			break;
		case Enter:
			if (!p[1].m[i][j].status)
				enter = true;
			break;
		case ESC:
			if (exit_menu() == 1)
			{
				free_m();
				menu(0);
			}
		}
	} while (!enter);
	return nn * i + j;
}

int scan_point2(Unit **m, const int nn, int &i, int &j, int &vector, int size)
{
	int x;
	bool enter = false, fcolor;

	do {
		fcolor = check_field(m, nn, i, j, vector, size);
		print_one(m, nn, i, j, vector, size, fcolor);
		x = _getch();
		switch (x)
		{
		case Down:
			if (i + 1 + (size  - 1) * vector < nn)
				i++;
			break;
		case Right:
			if (j + 1 + (size - 1) * !vector < nn)
				j++;
			break;
		case Up:
			if (i - 1 >= 0)
				i--;
			break;
		case Left:
			if (j - 1 >= 0)
				j--;
			break;
		case Space:
			vector = !vector;
			if (i + size > nn)
				i -= i + size - nn;
			if (j + size > nn)
				j -= j + size - nn;
			break;
		case Enter:
			if (check_field(m, nn, i, j, vector, size))
				enter = true;
			break;
		case ESC:
			if (exit_menu() == 1)
			{
				free_m();
				menu(0);
			}
		}
	} while (!enter);
	return nn * i + j;
}
#include "sea_battle.h"

/////////
int n_space(Unit** m, const int nn, bool status)
{
	int k = 0;
	for (int i = 0; i < nn; i++)
		for (int j = 0; j < nn; j++)
			if (m[i][j].status == status)
				k++;
	return k;
}

int random_shoot(Unit** m, const int nn)
{
	int k = 0;
	int i = 0, j = 0;
	int random = rand() % n_space(m, nn, 0);
	for (i = 0; i < nn; i++)
		for (j = 0; j < nn; j++)
		{
			if (m[i][j].status == 0)
				k++;
			if (k - 1 == random)
			{
				return j + nn * i;
			}
		}
	return 0;
}

////////

int check_area(Unit** m, const int nn, int i, int j, bool status)
{
	int check = 0;
	for (int k = i - 1; k <= i + 1; k++)
	{
		for (int p = j - 1; p <= j + 1; p++)
		{
			if (!(k >= 0 && k < nn && p >= 0 && p < nn))
				continue;
			if (!(i == k || j == p) || i == k && j == p)
				continue;
			if (m[k][p].status == 0 && !status || m[k][p].status == 1 && m[k][p].value > 0 && status)
				check++;
		}
	}
	return check;
}

int first_hit(Unit** m, const int nn, int i, int j)
{
	int random = rand() % check_area(m, nn, i, j, 0) + 1;
	int check = 0;
	for (int k = i - 1; k <= i + 1; k++)
	{
		for (int p = j - 1; p <= j + 1; p++)
		{
			if (!(k >= 0 && k < nn && p >= 0 && p < nn))
				continue;
			if (!(i == k || j == p) || i == k && j == p)
				continue;
			if (m[k][p].status == 0)
				check++;
			if (check == random)
				return nn * k + p;
		}
	}
	return 0;
}

int ship_head(Unit** m, const int nn, int i, int j)
{
	for (;;)
	{
		if (i != 0)
			if (m[i - 1][j].value > 0)
				i--;
		if (j != 0)
			if (m[i][j - 1].value > 0)
				j--;
		if ((i == 0 || m[i - 1][j].value == 0) && (j == 0 || m[i][j - 1].value == 0))
			break;
	}
	return nn * i + j;
}

int second_hit(Unit** m, const int nn, int i, int j, int random)
{
	int x = 0, y = 0;
	int head = ship_head(m, nn, i, j);
	int a = head / nn;
	int b = head % nn;
	int size = m[i][j].value;
	int check = 0;
	if (a + 1 < nn)
		if (m[a + 1][b].value > 0)
		{
			x = 0;
			y = 1;
		}
	if (b + 1 < nn)
		if (m[a][b + 1].value > 0)
		{
			x = 1;
			y = 0;
		}
	if (random != 0)
		random = rand() % random + 1;
	for (int k = a - 1 * y; k <= a + size * y; k++)
		for (int p = b - 1 * x; p <= b + size * x; p++)
		{
			if (!(k >= 0 && k < nn && p >= 0 && p < nn))
				continue;
			if (m[k][p].status == 0 && check_area(m, nn, k, p, 1) > 0)
			{
				check++;
				if (/*random != 0 &&*/ random == check)
					return k * nn + p;
			}
		}
	return second_hit(m, nn, i, j, check);
}

int aim_shoot(Unit** m, const int nn, int i, int j)
{
	if (check_area(m, nn, i, j, m[i][j].status) == 0)
	{
		return first_hit(m, nn, i, j);
	}
	else
	{
		return second_hit(m, nn, i, j, 0);
	}

	return 0;
}

/////////

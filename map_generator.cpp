#include "sea_battle.h"

Unit** create_squard(const int n)
{
	Unit** matrix = new Unit * [n];
	for (int i = 0; i < n; i++)
	{
		matrix[i] = new Unit[n];
	}
	return matrix;
}

Unit** zero_matrix(Unit** m, const int n, short value, bool status)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			m[i][j].value = value;
			m[i][j].status = status;
		}
	return m;
}

Unit** create_item(Unit** m, const int nn, int i, int j, int vector, int size)
{
	for (int k = i; k <= i + (size - 1) * vector; k++)
		for (int p = j; p <= j + (size - 1) * !vector; p++)
			m[k][p].value = size;
	return m;
}

bool check_field(Unit** m, const int nn, int i, int j, int vector, int size)
{
	if (!(i + (size - 1) * vector < nn && j + (size - 1) * !vector < nn))
		return false;
	for (int k = i - 1; k <= i + 1 + (size - 1) * vector; k++)
		for (int p = j - 1; p <= j + 1 + (size - 1) * !vector; p++)
		{
			if (!(k >= 0 && k < nn) || !(p >= 0 && p < nn))
				continue;
			if (m[k][p].value != 0)
				return false;
		}
	return true;
}

Unit** map_generator(Unit** m, const int nn, Modes &mode)
{
	int size = nn / 5 * 2;

	for (int z = 0; z < size; z++)
	{
		for (int y = 0; y <= z; y++)
		{
			int i, j, vector;
			bool flag;
			do
			{
				i = rand() % nn;
				j = rand() % nn;
				vector = rand() % 2;
				flag = check_field(m, nn, i, j, vector, size - z);
				if (flag)
				{
					if (mode.m_generator == 0 && mode.demo == 0)
						scan_point2(m, nn, i, j, vector, size - z);
					m = create_item(m, nn, i, j, vector, size - z);
				}
			} while (!flag);
		}
	}
	mode.m_generator = 1;
	return m;
}

Unit** map_generator2(Unit** m, const int nn, Modes &mode)
{
	int sh[3][4][2]
	{
		{ 4, 1 },
		{ 1, 5, 1, 4, 2, 3, 3, 2 },
		{ 2, 5, 2, 4, 4, 3, 7, 2 },
	};
	int step[]{ 1, 4, 4 };
	int index = nn / 5 - 1;

	for (int z = 0; z < step[index]; z++)
	{
		for (int y = 0; y < sh[index][z][0]; y++)
		{
			int i, j, vector;
			bool flag;
			do
			{
				i = rand() % nn;
				j = rand() % nn;
				vector = rand() % 2;
				flag = check_field(m, nn, i, j, vector, sh[index][z][1]);
				if (flag)
				{
					if (mode.m_generator == 0 && mode.demo == 0)
						scan_point2(m, nn, i, j, vector, sh[index][z][1]);
					m = create_item(m, nn, i, j, vector, sh[index][z][1]);
				}
			} while (!flag);
		}
	}
	mode.m_generator = 1;
	return m;
}

Unit** create_map(const int nn, Modes &mode)
{
	Unit** m = create_squard(nn);
	m = zero_matrix(m, nn, 0, 0);
	if (mode.mode == 0)
		m = map_generator(m, nn, mode);
	else
		m = map_generator2(m, nn, mode);
	return m;
}
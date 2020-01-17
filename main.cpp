#include <iostream>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

struct Unit 
{
	short value;
	bool status;
};

struct Player
{
	Unit **m;
	int last_hit;
	int r;
	int status;
	bool under_attack;
};

enum Color { Black = 0, Blue, Green, Cyan, Red, Magenta, Brown, LightGray, DarkGray, LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White };

void SetColor(int text, int background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void draw_item(string item, int color, int bg);
void print(Player *p, const int n, bool demo, int point, int poitn2);
Unit** create_squard(const int n);
Unit** matrix_value(Unit** m, const int n, short value, bool status);
Unit** create_item(Unit** m, const int nn, int i, int j, int vector, int size);
Unit** map_generator(Unit** m, const int nn, int size);
bool check_field(Unit** m, const int nn, int i, int j, int vector, int size);
Unit** area_of_the_destroyed_ship(Unit** m, const int nn, int i, int j);
bool ship_is_destroyed(Unit** m, const int nn, int i, int j);
int aim_shoot(Unit** m, int nn, int i, int j);
int second_hit(Unit** m, int nn, int i, int j, int random);
int first_hit(Unit** m, int nn, int i, int j);
int check_area(Unit** m, int nn, int i, int j, bool status);
int random_shoot(Unit** m, const int nn);
int ship_head(Unit** m, const int nn, int i, int j);
int n_space(Unit** m, const int nn, bool status);
int count_ships(Unit** m, const int nn, bool flag);
void print_unit(int r, const int nn);
void print_status(int status);
Player battle_shoot(Player p, const int nn, bool demo, int index);
void print_player(int index, bool demo);
int scan_point(Player *p, const int nn, int index);
void print_all(Player* p, const int nn, int index, bool demo, int point, int point2);
void DrawPoint(Unit p, bool demo, int color);
void sea_battle(const int nn, int max_size, bool demo);

int main()
{
	srand(time(0));
	int nn = 10;
	int max_size = 4;
	bool demo = true;

	sea_battle(nn, max_size, demo);

	getchar();
	getchar();
	return 0;
}

Unit** create_squard(const int n)
{
	Unit** matrix = new Unit* [n];
	for (int i = 0; i < n; i++)
	{
		matrix[i] = new Unit[n];
	}
	return matrix;
}

Unit** matrix_value(Unit** m, const int n, short value, bool status)
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
	int x = 0, y = 0;
	switch (vector % 2)
	{
	case 0:
		x = 1;
		y = 0;
		break;
	case 1:
		x = 0;
		y = 1;
		break;
	}
	for (int k = i; k <= i + (size - 1) * y; k++)
		for (int p = j; p <= j + (size - 1) * x; p++)
			m[k][p].value = size;
	return m;
}

void printX(Unit **m1, Unit** m2, const int n, bool demo, int point)
{
	string ship = { char(219), char(219) };
	string destroyed_ship = "XX";
	string miss = { char(177), char(177) };
	string sea = { char(177), char(177) };

	for (int i = 0; i < n; i++)
	{
		if (i + 1 > 9)
			cout << i + 1 << " ";
		else
			cout << " " << i + 1 << " ";

		for (int j = 0; j < n; j++)
		{
			if (m1[i][j].value != 0)
				if (m1[i][j].status == 0)
					draw_item(ship, White, Black);
				else
					draw_item(destroyed_ship, Black, White);
			else
				if (m1[i][j].status == 0)
					draw_item(sea, LightBlue, Black);
				else
					draw_item(miss, White, Black);
		}
		////////////////////
		cout << "\t\t";
		if (i + 1 > 9)
			cout << i + 1 << " ";
		else
			cout << " " << i + 1 << " ";
		for (int j = 0; j < n; j++)
		{
			if (i == point / n && j == point % n && !demo)
				cout << "OO";
			else
			if (m2[i][j].value != 0)
				if (m2[i][j].status == 0)
				{
					if (demo)
						draw_item(ship, White, Black);
					else
						draw_item(sea, LightBlue, Black);
				}
				else
					draw_item(destroyed_ship, Black, White);
			else
				if (m2[i][j].status == 0)
					draw_item(sea, LightBlue, Black);
				else
					draw_item(miss, White, Black);

		}
		cout << endl;
	}	char ch;
	cout << "   ";
	for (int i = 0; i < n; i++)
	{
		ch = 'A' + i;
		cout << ch << " ";
	}
	cout << "\t\t    ";
	for (int i = 0; i < n; i++)
	{
		ch = 'A' + i;
		cout << ch << " ";
	}
	cout << endl;
}

bool check_field(Unit** m, const int nn, int i, int j, int vector, int size)
{
	int x = 0, y = 0;
	switch (vector % 2)
	{
	case 0:
		x = 1;
		y = 0;
		break;
	case 1:
		x = 0;
		y = 1;
		break;
	}
	if (!(i + (size - 1) * y < nn && j + (size - 1) * x < nn))
		return false;
	for (int k = i - 1; k <= i + 1 + (size - 1) * y; k++)
		for (int p = j - 1; p <= j + 1 + (size - 1) * x; p++)
		{
			if (!(k >= 0 && k < nn) || !(p >= 0 && p < nn))
				continue;
			if (m[k][p].value != 0)
				return false;
		}
	return true;
}

Unit** map_generator(Unit** m, const int nn, int size)
{
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
					m = create_item(m, nn, i, j, vector, size - z);
			} while (!flag);
		}
	}
	return m;
}

int n_space(Unit** m, const int nn, bool status)
{
	int k = 0;
	for (int i = 0; i < nn; i++)
		for (int j = 0; j < nn; j++)
			if (m[i][j].status == status)
				k++;
	return k;
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

int random_shoot(Unit **m, const int nn)
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

int check_area(Unit **m, const int nn, int i, int j, bool status)
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

int first_hit(Unit **m, const int nn, int i, int j)
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

int aim_shoot(Unit** m,  const int nn, int i, int j)
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

bool ship_is_destroyed(Unit** m, const int nn, int i, int j)
{
	int x = 0, y = 0;
	int head = ship_head(m, nn, i, j);
	int a = head / nn;
	int b = head % nn;
	int size = m[i][j].value;

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
	for (int k = a; k <= a + (size - 1) * y; k++)
		for (int p = b; p <= b + (size - 1) * x; p++)
			if (m[k][p].status == 0)
				return false;
	return true;
}

Unit** area_of_the_destroyed_ship(Unit** m, const int nn, int i, int j)
{
	int x = 0, y = 0;
	int head = ship_head(m, nn, i, j);
	int a = head / nn;
	int b = head % nn;
	int size = m[a][b].value;
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
	for (int k = a - 1; k <= a + 1 + (size - 1) * y; k++)
		for (int p = b - 1; p <= b + 1 + (size - 1) * x; p++)
		{
			if (!(k >= 0 && k < nn) || !(p >= 0 && p < nn))
				continue;
			if (m[k][p].status == 0)
				m[k][p].status = 1;
		}
	return m;
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

void print_unit(int r, const int nn)
{
	char ch = 'a' + r % nn;
	cout << ch << " " << r / nn + 1 << " ";
}

void print_status(int status)
{
	switch (status)
	{
	case 0:
		cout << "  - Miss";
		break;
	case 1:
		cout << "  - Hit the ship";
		break;
	case 2:
		cout << "  - Ship has been destroyed";
		break;
	}
	cout << endl;
}
Player battle_shoot(Player p, const int nn, bool demo, int index)
{
	int r;
	int status;
	if (!demo && index == 1)
		r = p.r;
	else
	{
		if (!p.under_attack)
			r = random_shoot(p.m, nn);
		else
			r = aim_shoot(p.m, nn, p.last_hit / nn, p.last_hit % nn);
	}
	p.m[r / nn][r % nn].status = true;

	if (p.m[r / nn][r % nn].value > 0)
	{
		p.last_hit = r;
		
		if (!ship_is_destroyed(p.m, nn, r / nn, r % nn))
		{
			status = 1;
			p.under_attack = true;
		}
		else
		{
			p.m = area_of_the_destroyed_ship(p.m, nn, r / nn, r % nn);
			status = 2;
			p.under_attack = false;
		}
	}
	else
	{
		status = 0;
	}

	p.r = r;
	p.status = status;

	return p;
}

void print_player(int index, bool demo)
{if(demo)
	if (index == 1)
		cout << "Computer1  ";
	else
		cout << "Computer2  ";
else
{
	if (index == 1)
		cout << "Player    ";
	else
		cout << "Computer  ";
}
}

int scan_point(Player* p, const int nn, int index)
{
	int i = p[1].r / nn;
	int j = p[1].r % nn;
	/*
	system("cls");
	print(p[0].m, p[1].m, nn, false, p[1].r);
	print_player(index);
	print_unit(p[index].r, nn);
	print_status(p[index].status);
	*/
	print_all(p, nn, index, false, p[1].r, p[0].r);
	int x;
	bool enter = false;
	do {
		x = _getch();
		switch (x)
		{
		case 80:
			if(i + 1 < nn)
				i++;
			break;
		case 77:
			if (j + 1 < nn)
			j++;
			break;
		case 72:
			if(i - 1 >= 0)
				i--;
			break;
		case 75:
			if (j - 1 >= 0)
				j--;
			break;
		case 13:
			if (!p[1].m[i][j].status)
				enter = true;
		}
		print_all(p, nn, index, false, nn * i + j, p[0].r);
		/*system("cls");
		print(p[0].m, p[1].m, nn, false, nn * i + j);
		print_player(index);
		print_unit(p[index].r, nn);
		print_status(p[index].status);*/
		//printf("%d", x);
	} while (!enter);
	return nn * i + j;
}

void print_all(Player* p, const int nn, int index, bool demo, int point, int point2)
{
	system("cls");
	print(p, nn, demo, point, point2);
	cout << endl;
	print_player(1, demo);
	if (p[1].status != -1)
	{
		print_unit(p[1].r, nn);
		print_status(p[1].status);
	}
	else
	{
		cout << endl;
	}
	print_player(0, demo);
	if (p[0].status != -1)
	{
		print_unit(p[0].r, nn);
		print_status(p[0].status);
	}
	else
	{
		cout << endl;
	}
	if (!demo)
	{
		cout << "Point: ";
		print_unit(point, nn);
		cout << endl;
	}
}

void draw_item(string item, int color, int bg)
{
	SetColor(color, bg);
	cout << item;
	SetColor(White, Black);
}

void DrawUnit(Unit p, bool demo)
{	string ship = { char(219), char(219) };
	string destroyed_ship = "XX";
	string miss = { char(177), char(177) };
	string sea = { char(177), char(177) };
	if(p.value > 0)
		if(!p.status)
			if(demo)
				draw_item(ship, White, Black);
			else
				draw_item(sea, LightBlue, Black);
		else
			draw_item(destroyed_ship, Black, White);
	else
		if(!p.status)
			draw_item(sea, LightBlue, Black);
		else
			draw_item(miss, White, Black);
}

void DrawPoint(Unit p, bool demo, int color)
{
	string ship = { char(219), char(219) };
	string destroyed_ship = "XX";
	string miss = { char(177), char(177) };
	string sea = { char(177), char(177) };
	if (p.value > 0)
		if (!p.status)
			if (demo)
				draw_item(ship, color, Black);
			else
				draw_item(sea, Black, color);
		else
			draw_item(destroyed_ship, Black, color);
	else
		if (!p.status)
			draw_item(sea, Black, color);
		else
			draw_item(miss, Black, color);
}

void print(Player *p, const int n, bool demo, int point, int point2)
{
	for (int i = 0; i < n; i++)
	{
		if (i + 1 > 9)
			cout << i + 1 << " ";
		else
			cout << " " << i + 1 << " ";

		for (int j = 0; j < n; j++)
		{
			if (i == point2 / n && j == point2 % n && p[0].status != -1)
				DrawPoint(p[0].m[i][j], true, LightGreen);
			else
				DrawUnit(p[0].m[i][j], true);
		}
		////////////////////
		cout << "\t\t";
		if (i + 1 > 9)
			cout << i + 1 << " ";
		else
			cout << " " << i + 1 << " ";
		for (int j = 0; j < n; j++)
		{
			if (i == point / n && j == point % n && (p[1].status != -1 || !demo))
				DrawPoint(p[1].m[i][j], demo, LightGreen);
			else
				DrawUnit(p[1].m[i][j], demo);
		}
		cout << endl;
	}	char ch;
	cout << "   ";
	for (int i = 0; i < n; i++)
	{
		ch = 'A' + i;
		cout << ch << " ";
	}
	cout << "\t\t    ";
	for (int i = 0; i < n; i++)
	{
		ch = 'A' + i;
		cout << ch << " ";
	}
	cout << endl;
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
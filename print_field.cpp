#include "header.h"

void print(Player* p, const int n, bool demo, int point, int point2)
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
				DrawPoint(p[0].m[i][j], true, LightGreen, Red);
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
				DrawPoint(p[1].m[i][j], demo, LightGreen, Red);
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

void print_player(int index, bool demo)
{
	if (demo)
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
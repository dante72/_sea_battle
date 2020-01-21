#include <windows.h>
#include "sea_battle.h"

using namespace std;

void SetColor(int text, int background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void draw_item(string item, int color, int bg)
{
	SetColor(color, bg);
	cout << item;
	SetColor(White, Black);
}

void DrawUnit(Unit p, bool demo)
{
	string ship = { char(219), char(219) };
	string destroyed_ship = "XX";
	string miss = { char(177), char(177) };
	string sea = { char(177), char(177) };
	if (p.value > 0)
		if (!p.status)
			if (demo)
				draw_item(ship, White, Black);
			else
				draw_item(sea, Cyan, Black);
		else
			draw_item(destroyed_ship, Black, White);
	else
		if (!p.status)
			draw_item(sea, Cyan, Black);
		else
			draw_item(miss, White, Black);
}

void DrawPoint(Unit p, bool demo, int color, int color2)
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
			draw_item(destroyed_ship, LightGray, color2);
	else
		if (!p.status)
			draw_item(sea, Black, color);
		else
			draw_item(miss, DarkGray, color2);
}

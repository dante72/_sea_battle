#include <windows.h>
#include "sea_battle.h"

int index = 0;
enum Color { Black = 0, Blue, Green, Cyan, Red, Magenta, Brown, LightGray, DarkGray, LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White };
char ship[] = { char(219), char(219), '\0' };
char destroyed_ship[] = "XX";
char miss[] = { char(177), char(177), '\0' };
char sea[] = { char(177), char(177), '\0' };

int th[][8]	{	//ship			 sea			dship			miss
				{White, Black, Cyan, Black, Black, White, White, Black},
				{Yellow, Black, Blue, Cyan, Black, Yellow, Yellow, Cyan},
			};
int thp[][8]	{
					{LightGreen, Black, Black, LightGreen, LightGray, Red, DarkGray, Red},
					{LightGreen, Black, Black, LightGreen, LightGray, Red, DarkGray, Red}
				};
int thm[][2]	{
					{White,  Black},
					{Yellow,  Cyan}
				};

void SetColor(int text, int background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void draw_item(char *item, int color, int bg)
{
	SetColor(color, bg);
	printf("%s", item);
	SetColor(thm[index][0], thm[index][1]);
}

void DrawUnit(Unit p, bool demo)
{
	int t_sh = th[index][0], bg_sh = th[index][1],\
		t_sea = th[index][2], bg_sea = th[index][3], \
		t_dsh = th[index][4], bg_dsh = th[index][5], \
		t_miss = th[index][6], bg_miss = th[index][7];

	if (p.value > 0)
		if (!p.status)
			if (demo)
				draw_item(ship, t_sh, bg_sh);
			else
				draw_item(sea, t_sea, bg_sea);
		else
			draw_item(destroyed_ship, t_dsh, bg_dsh);
	else
		if (!p.status)
			draw_item(sea, t_sea, bg_sea);
		else
			draw_item(miss, t_miss, bg_miss);
}

void DrawPoint(Unit p, bool demo)
{
	int t_sh = thp[index][0], bg_sh = thp[index][1], \
		t_sea = thp[index][2], bg_sea = thp[index][3], \
		t_dsh = thp[index][4], bg_dsh = thp[index][5], \
		t_miss = thp[index][6], bg_miss = thp[index][7];

	if (p.value > 0)
		if (!p.status)
			if (demo)
				draw_item(ship, t_sh, bg_sh);
			else
				draw_item(sea, t_sea, bg_sea);
		else
			draw_item(destroyed_ship, t_dsh, bg_dsh);
	else
		if (!p.status)
			draw_item(sea, t_sea, bg_sea);
		else
			draw_item(miss, t_miss, bg_miss);
}

void change_theme(int theme)
{	
	index = theme;
	SetColor(thm[index][0], thm[index][1]);
}

void DrawPoint2(Unit p, bool status)
{
	int t_sh = thp[index][0], bg_sh = thp[index][1], \
		t_sea = thp[index][2], bg_sea = thp[index][3], \
		t_dsh = thp[index][4], bg_dsh = thp[index][5], \
		t_miss = thp[index][6], bg_miss = thp[index][7];

	if (status)
		draw_item(ship, t_sh, bg_sh);
	else
		draw_item(ship, bg_dsh, t_dsh);
}


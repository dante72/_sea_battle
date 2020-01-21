#include "sea_battle.h"
#ifndef MENU_H
#define MENU_H

struct Menu
{
	short name;
	short choose;
	short next;
};

void menu(int n_menu);
Menu* change_menu(Menu* m, int index);
int print_menu(int i);
int print_menu2(int i);

#endif
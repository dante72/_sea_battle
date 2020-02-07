#include <iostream>

#ifndef SEA_BATTLE_H
#define SEA_BATTLE_H

struct Unit
{
	short value;
	bool status;
};

struct Player
{
	Unit** m;
	int last_hit;
	int r;
	int status;
	bool under_attack;
};

enum Color { Black = 0, Blue, Green, Cyan, Red, Magenta, Brown, LightGray, DarkGray, LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White };

enum Buttons {
	ESC = 27,
	Enter = 13,
	Down = 80,
	Up = 72,
	Right = 77,
	Left = 75
};

struct Menu
{
	short name;
	short choose;
	short count;
};

Unit** create_squard(const int n);
Unit** zero_matrix(Unit** m, const int n, short value, bool status);
Unit** create_item(Unit** m, const int nn, int i, int j, int vector, int size);
bool check_field(Unit** m, const int nn, int i, int j, int vector, int size);
Unit** map_generator(Unit** m, const int nn);
Unit** create_map(const int nn, int mode);
Unit** map_generator2(Unit** m, const int nn);

int n_space(Unit** m, const int nn, bool status);
int random_shoot(Unit** m, const int nn);
int check_area(Unit** m, int nn, int i, int j, bool status);
int first_hit(Unit** m, int nn, int i, int j);
int ship_head(Unit** m, const int nn, int i, int j);
int second_hit(Unit** m, int nn, int i, int j, int random);
int aim_shoot(Unit** m, int nn, int i, int j);
int scan_point(Player* p, const int nn, int index);

bool ship_is_destroyed(Unit** m, const int nn, int i, int j);
Unit** area_of_the_destroyed_ship(Unit** m, const int nn, int i, int j);
Player *battle_shoot(Player *pl, const int nn, bool demo, int index);
int count_ships(Unit** m, const int nn, bool flag);
void sea_battle(const int nn, bool demo, int mode);

void print(Player* p, const int n, bool demo, int point, int poitn2);
void print_player(int index, bool demo);
void print_unit(int r, const int nn);
void print_status(int status);
void print_all(Player* p, const int nn, int index, bool demo, int point, int point2);

void SetColor(int text, int background);
void draw_item(char *item, int color, int bg);
void DrawUnit(Unit p, bool demo);
void DrawPoint(Unit p, bool demo);
void change_theme(int theme);

void print_menu(char str[][20], const int n, int i);
Menu* change_menu(Menu* m, char str[][20], int index);
int menu(int n_menu);
int exit_menu();

#endif


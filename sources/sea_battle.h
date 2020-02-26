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

struct Modes 
{
	int mode;
	int m_generator;
	bool demo;
};

enum Buttons {
	ESC = 27,
	Enter = 13,
	Down = 80,
	Up = 72,
	Right = 77,
	Left = 75,
	Space = 32
};

struct Menu
{
	short name;
	short choose;
	short count;
};

Unit** create_squard(const int n);
void ft_delete(Unit** matrix);
Unit** zero_matrix(Unit** m, const int n, short value, bool status);
Unit** create_item(Unit** m, const int nn, int i, int j, int vector, int size);
bool check_field(Unit** m, const int nn, int i, int j, int vector, int size);
Unit** map_generator(Unit** m, const int nn, Modes &mode);
Unit** create_map(const int nn);
Unit** map_gen(Unit** m, const int nn, Modes &mode);
Unit** map_generator2(Unit** m, const int nn, Modes &mode);
int scan_point2(Unit** m, const int nn, int &i, int &j, int &vector, int size);

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
int sea_battle(const int nn, Modes mode);
void free_m();
int press_button();

void print(Player* p, const int n, bool demo, int point, int poitn2);
void print_player(int index, bool demo);
void print_unit(int r, const int nn);
void print_status(int status);
void print_all(Player* p, const int nn, int index, bool demo, int point, int point2);
void print_one(Unit** m, const int n, int i, int j, int vector, int size, bool status);

void SetColor(int text, int background);
void draw_item(char *item, int color, int bg);
void DrawUnit(Unit p, bool demo);
void DrawPoint(Unit p, bool demo);
void change_theme(int theme);
void DrawPoint2(Unit p, bool status);

void print_menu(char str[][20], const int n, int i);
Menu* change_menu(Menu* m, char str[][20], int index);
int menu(int n_menu);
int exit_menu();

#endif


#include <ctime>
#include "header.h"

using namespace std;

int main()
{
	srand(time(0));
	int nn = 10;
	int max_size = 4;
	bool demo = false;

	sea_battle(nn, max_size, demo);

	getchar();
	getchar();
	return 0;
}
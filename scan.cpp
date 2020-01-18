#include <conio.h>
#include "header.h"


int scan_point(Player* p, const int nn, int index)
{
	int i = p[1].r / nn;
	int j = p[1].r % nn;

	int x;
	bool enter = false;
	do {
		print_all(p, nn, index, false, nn * i + j, p[0].r);
		x = _getch();
		switch (x)
		{
		case 80:
			if (i + 1 < nn)
				i++;
			break;
		case 77:
			if (j + 1 < nn)
				j++;
			break;
		case 72:
			if (i - 1 >= 0)
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

	} while (!enter);
	return nn * i + j;
}
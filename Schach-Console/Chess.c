#include "Chess.h"

int main() {
	getch();
}

void print_field(char field[8][8], int offsetx, int offsety) {
	int x, y;
	for (x = 0; x < 8; x++) {
		for (y = 0; y < 8; y++) {
			gotoXY(x, y);
			printf("%c", field[x][y]);
		}
	}
}
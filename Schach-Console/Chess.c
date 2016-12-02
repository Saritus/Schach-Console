#include "Chess.h"

int main() {
	char* field = create_start_field();
	getch();
}

void print_field(char field[8][8], int offsetx, int offsety) {
	int x, y;
	for (y = 0; y < 8; y++) {
		for (x = 0; x < 8; x++) {
			gotoXY(x, y);
			printf("%c", field[y][x]);
		}
		printf("\n");
	}
}

char* create_start_field() {
	char field[8][8];

	char black[9] = { 'T', 'S', 'L', 'D', 'K', 'L', 'S', 'T', 'B' };
	char white[9] = { 't', 's', 'l', 'd', 'k', 'l', 's', 't', 'b' };

	int x, y;
	for (y = 0; y < y; y++) {
		switch (y) {
		case 0:
			for (x = 0; x < 8; x++) {
				field[y][x] = black[x];
			}
			break;
		case 1:
			for (x = 0; x < 8; x++) {
				field[y][x] = 'B';
			}
			break;
		case 6:
			for (x = 0; x < 8; x++) {
				field[y][x] = 'b';
			}
			break;
		case 7:
			for (x = 0; x < 8; x++) {
				field[y][x] = white[x];
			}
			break;
		default:
			for (x = 0; x < 8; x++) {
				field[y][x] = ' ';
			}
			break;
		}
	}

	return field;
}
#include "Chess.h"

int main() {
	char field[8][8];
	reset_field(field);
	
	load_file("test.txt", field);
	//save_file("test.txt", field);

	print_field(field, 6, 3);
	print_border(4, 2);

	getch();
}

void print_field(char field[8][8], int offsetx, int offsety) {
	int x, y;
	for (y = 0; y < 8; y++) {
		for (x = 0; x < 8; x++) {
			gotoXY(2*x + offsetx, y + offsety);
			printf("%c", field[y][x]);
		}
		//printf("\n");
	}
}

void reset_field(char field[8][8]) {
	
	char black[9] = { 'T', 'S', 'L', 'D', 'K', 'L', 'S', 'T' };
	char white[9] = { 't', 's', 'l', 'd', 'k', 'l', 's', 't' };

	int x, y;
	for (y = 0; y < 8; y++) {
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
}

void print_border(int offsetx, int offsety) {
	int x, y;
	for (y = offsety; y < offsety+10; y++) {
		for (x = offsetx; x < offsetx+19; x++) {
			gotoXY(x, y);
			if (x == offsetx || y == offsety || x == offsetx + 18 || y == offsety + 9) {
				printf("+");
			}
		}
	}
}

void load_file(char* filename, char field[8][8]) {
	FILE *f = fopen(filename, "r");
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			field[i][j] = (char)fgetc(f);
		}
	}
	fclose(f);
}

void save_file(char* filename, char field[8][8]) {
	FILE *f = fopen(filename, "w");
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			fputc(field[i][j], f);
		}
	}
	fclose(f);
}
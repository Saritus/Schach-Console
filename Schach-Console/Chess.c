#include "Chess.h"

int main() {
	char field[8][8];
	int player = 1;
	reset_field(field);

	//load_file("test.txt", field);
	//save_file("test.txt", field);


	char next = 'g';
	while (next != 'q') {
		system("cls");
		print_surface(field, player);
		next = input(field, player);
		player = (next == 'n') && (player == 1) ? 2 : 1;
	}
}

void print_surface(int field[8][8], int player) {
	print_player(2, 1, player);
	print_letters(3, 4);
	print_border(5, 5);
	print_field(field, 7, 6);
}

void print_player(int x, int y, int player) {
	gotoXY(x, y);
	printf("Spieler %d ist dran", player);
}

void print_field(char field[8][8], int offsetx, int offsety) {
	int x, y;
	for (y = 0; y < 8; y++) {
		for (x = 0; x < 8; x++) {
			gotoXY(4 * x + offsetx, 2 * y + offsety);
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

void print_letters(int offsetx, int offsety) {
	int i;
	for (i = 0; i < 8; i++) {
		//TOP
		gotoXY(4 * i + offsetx + 4, offsety);
		printf("%c", i + 'a');

		//BOTTOM
		gotoXY(4 * i + offsetx + 4, offsety + 18);
		printf("%c", i + 'a');

		//LEFT
		gotoXY(offsetx, 2 * i + offsety + 2);
		printf("%d", 8 - i);

		//RIGHT
		gotoXY(offsetx + 36, 2 * i + offsety + 2);
		printf("%d", 8 - i);
	}
}

void print_border(int offsetx, int offsety) {
	for (int x = 0; x < 33; x++) {
		for (int y = 0; y < 17; y++) {
			gotoXY(x + offsetx, y + offsety);
			int nr = 2 * (x % 4 == 0) + (y % 2 == 0);
			switch (nr) {
			case 3:
				printf("+");
				break;
			case 2:
				printf("|");
				break;
			case 1:
				printf("-");
				break;
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

char input(char field[8][8], int player) {
	char input[5];
	gotoXY(4, 24);
	printf("Nachster Zug: ");
	scanf_s("%4c", &input, _countof(input) - 1);
	input[4] = '\0';
	clear_stdin();

	gotoXY(4, 25);
	//printf("%s", input);

	if (!strcmp(input, "quit")) {
		return 'q';
	}

	int move[4];
	if (evaluate_input(input, move) && is_move_ok(field, move, player)) {
		execute_move(field, move);
		return 'n';
	}
	else {
		return 'a';
	}
}

void clear_stdin() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {};
}

int evaluate_input(char* input, int move[4]) {
	if (is_letter(input[0])) {
		move[0] = input[0] - 'a';
	}
	else {
		return 0;
	}
	if (is_number(input[1])) {
		move[1] = 7 - (input[1] - '1');
	}
	else {
		return 0;
	}
	if (is_letter(input[2])) {
		move[2] = input[2] - 'a';
	}
	else {
		return 0;
	}
	if (is_number(input[3])) {
		move[3] = 7 - (input[3] - '1');
	}
	else {
		return 0;
	}
	return 1;
}

int is_letter(char letter) {
	return ((letter >= 'a') && (letter <= 'h'));
}

int is_number(char number) {
	return ((number >= '1') && (number <= '8'));
}

int execute_move(char field[8][8], int move[4]) {
	field[move[3]][move[2]] = field[move[1]][move[0]];
	field[move[1]][move[0]] = ' ';
}

int is_move_ok(char field[8][8], int move[4], int player) {
	char figur = field[move[1]][move[0]];

	// cannot move empty space
	if (figur == ' ') {
		return 0;
	}

	// player 1 can only move lower letters
	if ((player == 1) && ('A' <= figur) && (figur <= 'Z')) {
		return 0;
	}

	// player 2 can only move lower letters
	if ((player == 2) && ('a' <= figur) && (figur <= 'z')) {
		return 0;
	}
	return 1;
}
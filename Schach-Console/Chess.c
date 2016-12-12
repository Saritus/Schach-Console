#include "Chess.h"

typedef int bool;
#define true 1
#define false 0

struct Chessmove{
	bool ok;
	int player;
	int von_spalte;
	int von_zeile;
	int nach_spalte;
	int nach_zeile;
};

int main() {
	char field[8][8];
	int player = 1;
	int turn = 0;
	reset_field(field);

	//load_file("test.txt", field);
	//save_file("test.txt", field);

	remove("history.txt");

	char next = 'g';
	while (next != 'q') {
		system("cls");
		print_surface(field, player);
		next = input(field, player);
		if (next == 'n') {
			player = (player == 1) ? 2 : 1;
			turn++;
			writeLine("history.txt", field);
		}
		if (next == 'u') {
			loadLine("history.txt", --turn, field);
		}
	}
}

void print_surface(char field[8][8], int player) {
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
	int x, y;
	for (x = 0; x < 33; x++) {
		for (y = 0; y < 17; y++) {
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
	int i, j;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			field[i][j] = (char)fgetc(f);
		}
	}
	fclose(f);
}

void save_file(char* filename, char field[8][8]) {
	FILE *f = fopen(filename, "w");
	int i, j;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
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

	if (!strcmp(input, "save")) {
		return 's';
	}

	if (!strcmp(input, "undo")) {
		return 'u';
	}

	struct Chessmove move = evaluate_input(input);
	move.player = player;
	if (move.ok && is_move_ok(field, move)) {
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

struct Chessmove evaluate_input(char* input) {
	struct Chessmove move = { true };
	if (is_letter(input[0])) {
		move.von_spalte = input[0] - 'a';
	}
	else {
		move.ok = false;
	}
	if (is_number(input[1])) {
		move.von_zeile = 7 - (input[1] - '1');
	}
	else {
		move.ok = false;
	}
	if (is_letter(input[2])) {
		move.nach_spalte = input[2] - 'a';
	}
	else {
		move.ok = false;
	}
	if (is_number(input[3])) {
		move.nach_zeile = 7 - (input[3] - '1');
	}
	else {
		move.ok = false;
	}
	return move;
}

int is_letter(char letter) {
	return ((letter >= 'a') && (letter <= 'h'));
}

int is_number(char number) {
	return ((number >= '1') && (number <= '8'));
}

void execute_move(char field[8][8], struct Chessmove move) {
	field[move.nach_zeile][move.nach_spalte] = field[move.von_zeile][move.von_spalte];
	field[move.von_zeile][move.von_spalte] = ' ';
}

int is_move_ok(char field[8][8], struct Chessmove move) {
	char figur = field[move.von_zeile][move.von_spalte];

	// cannot move empty space
	if (figur == ' ') {
		return 0;
	}

	// player 1 can only move lower letters
	if ((move.player == 1) && ('A' <= figur) && (figur <= 'Z')) {
		return 0;
	}

	// player 2 can only move lower letters
	if ((move.player == 2) && ('a' <= figur) && (figur <= 'z')) {
		return 0;
	}
	return 1;
}

char* readLine(char* filename, int linenumber) {
	FILE *file = fopen(filename, "r");
	int count = 1;
	if (file != NULL) {
		static char line[256]; /* or other suitable maximum line size */
		while (fgets(line, sizeof line, file) != NULL) /* read a line */
		{
			if (count == linenumber)
			{
				//use line or in a function return it
				//in case of a return first close the file with "fclose(file);"
				fclose(file);
				return line;
			}
			else
			{
				count++;
			}
		}
		fclose(file);
	}
	else {
		//file doesn't exist
		return NULL;
	}
	return NULL; // should never happen
}

int writeLine(char* filename, char field[8][8]) {
	FILE *f = fopen(filename, "a");
	int i, j;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			fputc(field[i][j], f);
		}
	}
	fputc('\n', f);
	fclose(f);
}

void loadLine(char* filename, int linenumber, char field[8][8]) {
	char* line = readLine(filename, linenumber);
	if (line) {
		int i, j;
		for (i = 0; i < 8; i++) {
			for (j = 0; j < 8; j++) {
				field[i][j] = line[i * 8 + j];
			}
		}
	}
}
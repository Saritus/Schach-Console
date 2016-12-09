#include "Chess.h"

int main() {
	char field[8][8];
	int player = 1;
	reset_field(field);

	//load_file("test.txt", field);
	//save_file("test.txt", field);


	int quit = 0;
	while (!quit) {
		system("cls");
		print_player(2, 1, player);
		print_letters(2, 3);
		print_border(3, 4);
		print_field(field, 5, 5);
		quit = input(field, player);
		player = player == 1 ? 2 : 1;
	}
}

void print_player(int x, int y, int player) {
	gotoXY(x, y);
	printf("Spieler %d ist dran", player);
}

void print_field(char field[8][8], int offsetx, int offsety) {
	int x, y;
	for (y = 0; y < 8; y++) {
		for (x = 0; x < 8; x++) {
			gotoXY(2 * x + offsetx, y + offsety);
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
		gotoXY(2 * i + offsetx + 3, offsety);
		printf("%c", i + 'a');

		//BOTTOM
		gotoXY(2 * i + offsetx + 3, offsety + 11);
		printf("%c", i + 'a');

		//LEFT
		gotoXY(offsetx, i + offsety + 2);
		printf("%d", 8 - i);

		//RIGHT
		gotoXY(offsetx + 20, i + offsety + 2);
		printf("%d", 8 - i);
	}
}

void print_border(int offsetx, int offsety) {
	for (int x = 0; x < 19; x++) {
		for (int y = 0; y < 10; y++) {
			gotoXY(x + offsetx, y + offsety);
			int nr = 2 * (x == 0) + (y == 0) + 2 * (x == 18) + (y == 9);
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
	gotoXY(4, 16);
	printf("Nachster Zug: ");
	scanf_s("%4c", &input, _countof(input) - 1);
	input[4] = '\0';
	clear_stdin();

	gotoXY(4, 17);
	//printf("%s", input);

	if (!strcmp(input, "quit")) {
		return 1;
	}

	int move[4];
	if (evaluate_input(input, move) && is_move_ok(field, move, player)) {
		execute_move(field, move);
	}

	gotoXY(4, 18);
	//printf("%d.%d.%d.%d", move[0], move[1], move[2], move[3]);

	

	//getch();

	return 0;
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

int is_move_ok(char field[8][8], int move[4]) {
	char figur = field[move[1]][move[0]];
	if (figur == ' ') {
		return 0;
	}
	return 1;
}